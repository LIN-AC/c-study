/*
 * @Author: LIN-AC 1335954640@qq.com
 * @Date: 2022-08-14 15:45:37
 * @LastEditors: LIN-AC 1335954640@qq.com
 * @LastEditTime: 2022-08-14 16:35:53
 * @FilePath: \code\LinkedList\Queue.cc
 * @Description:
 *
 * Copyright (c) 2022 by LIN-AC 1335954640@qq.com, All Rights Reserved.
 */
#include "queue.hh"
#include <cstdlib>
#include <ctime>
Queue::Queue(int qs) : qsize_(qs)
{
    front_ = rear_ = nullptr;
    items_ = 0;
}

Queue::~Queue()
{
    Node *temp;
    while (front_ != nullptr)
    {
        temp = front_;
        front_ = front_->next;
        delete temp;
    }
}
bool Queue::isempty() const
{
    return items_ == 0;
}
bool Queue::isfull() const
{
    return items_ == qsize_;
}
bool Queue::enqueue(const Item &item)
{
    if (isfull())
        return false;
    Node *add = new Node;
    add->item = item;
    add->next = nullptr;
    ++items_;
    if (front_ == nullptr)
    {
        front_ = add;
    }
    else
        rear_->next = add;
    rear_ = add;
    return true;
}
bool Queue::dequeue(Item &item)
{
    if (isempty())
        return false;
    item = front_->item;
    --items_;
    Node *temp = front_;
    front_ = front_->next;
    delete temp;
    if (items_ == 0)
        rear_ = nullptr;
    return true;
}

void Customer::set(long when)
{
    processtime_ = std::rand() % 3 + 1;
    arrive_ = when;
}
int main()
{
    Queue q;

    return 0;
}