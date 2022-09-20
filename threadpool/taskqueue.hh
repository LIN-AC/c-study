#pragma once

#include <queue>
#include <mutex>

template <typename T>
class Taskqueue
{
private:
    std::mutex mtx_;
    std::queue<T> taskqueue_;
    size_t size_;

public:
    Taskqueue(const size_t size = 1024) : size_(size)
    {
    }
    ~Taskqueue()
    {
    }
    bool empty()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        return taskqueue_.empty();
    }
    bool full()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        return taskqueue_.size() == size_;
    }
    bool enqueue(const T &t)
    {
        if (full())
            return false;
        std::unique_lock<std::mutex> lock(mtx_);
        taskqueue_.push(t);
        return true;
    }
    bool dequeue(T &t)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (empty())
            return false;
        t = std::move(taskqueue_.front());
        taskqueue_.pop();
        return true;
    }
};
