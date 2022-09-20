/*
 * @Author: LIN-AC 1335954640@qq.com
 * @Date: 2022-08-25 15:52:33
 * @LastEditors: LIN-AC 1335954640@qq.com
 * @LastEditTime: 2022-08-25 16:50:09
 * @FilePath: \code\priority_queue\priorityqueue.cc
 * @Description:
 *
 * Copyright (c) 2022 by LIN-AC 1335954640@qq.com, All Rights Reserved.
 */
#include "priorityqueue.hh"
#include <iostream>

template <typename Type>
priorityQueue<Type>::priorityQueue()
{
    size_ = 0;
}

template <typename Type>
priorityQueue<Type>::~priorityQueue()
{
}

template <typename Type>
priorityQueue<Type>::priorityQueue(int size)
    : size_(size)
{
    count_.resize(size);
}

template <typename Type>
int priorityQueue<Type>::size()
{
    return size_;
}

template <typename Type>
Type priorityQueue<Type>::maximum()
{
    return size_ > 0 ? count_[0] : 0;
}

template <typename Type>
void priorityQueue<Type>::push(Type &t)
{
    count_.push_back(t);
    ++size_;
    maxHeap(); //上浮
}

template <typename Type>
void priorityQueue<Type>::pop()
{
    int h = 0, t;
    count_[0] = -1;
    std::swap(count_[0], count_[--size_]);
    int index = size_ / 2;
    while (h < index)
    {
        t = 2 * h + 1;
        t = count_[t] > count_[t + 1] ? t : t + 1;
        if (count_[h] > count_[t])
            break;
        std::swap(count_[h], count_[t]);
        h = t;
    }
}
template <typename Type>
void priorityQueue<Type>::destroy()
{
    if (count_)
        delete[] count_;
}

template <typename Type>
void priorityQueue<Type>::maxHeap()
{
    int hole = count_.size() - 1; //新插入元素位置
    for (; hole && count_[hole] > count_[hole / 2]; hole >>= 1)
    {
        std::swap(count_[hole], count_[hole / 2]);
    }
}

int main()
{
    using namespace std;
    priorityQueue<int> queue;
    for (int i = 0; i < 10; ++i)
    {
        queue.push(i);
        cout << queue.maximum() << ' ';
    }
    cout << '\n';
    for (int i = 0; i < 5; ++i)
    {
        cout << queue.maximum() << ' ';
        queue.pop();
    }
    return 0;
}