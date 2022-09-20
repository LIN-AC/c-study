#pragma once

#include "taskqueue.hh"

#include <vector>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <utility>
class Threadpool
{
private:
    class Threadworker
    {
    private:
        int pid_;          //线程id
        Threadpool *pool_; //线程池指针

    public:
        Threadworker(Threadpool *threadpool, const int pid)
            : pid_(pid), pool_(threadpool)
        {
        }
        ~Threadworker()
        {
        }
        //重载()运算符
        void operator()()
        {
            std::function<void()> func;
            bool dequeued;
            while (!pool_->shutdowned_)
            {
                {
                    std::unique_lock<std::mutex> lock(pool_->mtx_); //加锁
                    if (pool_->task_.empty())
                    {
                        pool_->cv_lock_.wait(lock);
                    }
                    dequeued = pool_->task_.dequeue(func);
                }
                if (dequeued)
                {
                    func();
                }
            }
        }
    };

    bool shutdowned_;                       //线程池是否关闭
    std::mutex mtx_;                        //同步锁
    std::condition_variable cv_lock_;       //同步信号量
    std::vector<std::thread> threadpool_;   //线程池
    Taskqueue<std::function<void()>> task_; //任务等待队列
public:
    Threadpool(const int size)
        : threadpool_(std::vector<std::thread>(size)), shutdowned_(false)
    {
    }

    ~Threadpool() {}

    //禁止复制构造以及移动构造
    Threadpool(const Threadpool &) = delete;
    Threadpool(Threadpool &&) = delete;
    Threadpool &operator=(const Threadpool &) = delete;
    Threadpool &operator=(Threadpool &&) = delete;

    void init()
    { //初始化线程池
        for (int i = 0; i < threadpool_.size(); ++i)
        {
            threadpool_[i] = std::thread(Threadworker(this, i));
        }
    }

    void shutdown()
    {
        shutdowned_ = true;
        cv_lock_.notify_all();
        for (int i = 0; i < threadpool_.size(); ++i)
        {
            if (threadpool_[i].joinable())
            {
                threadpool_[i].join();
            }
        }
    }

    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        std::function<void()> wrapper_func = [task_ptr]()
        {
            (*task_ptr)();
        };
        task_.enqueue(wrapper_func);
        cv_lock_.notify_one();
        return task_ptr->get_future(); //执行
    }
};
