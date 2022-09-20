/*
 * @Author: LIN-AC 1335954640@qq.com
 * @Date: 2022-08-25 15:44:48
 * @LastEditors: LIN-AC 1335954640@qq.com
 * @LastEditTime: 2022-08-25 16:38:14
 * @FilePath: \code\priority_queue\priorityqueue.hh
 * @Description:
 *
 * Copyright (c) 2022 by LIN-AC 1335954640@qq.com, All Rights Reserved.
 */

#include <vector>
#include <algorithm>
using std::vector;

template <typename Type>
class priorityQueue
{
private:
    vector<Type> count_;
    int size_;

public:
    priorityQueue();
    priorityQueue(int size);
    ~priorityQueue();

public:
    Type maximum();    //获取最大值
    void maxHeap();    //维持大根堆
    void push(Type &); //加入元素
    void pop();        //弹出元素
    // void resize();     //扩容
    int size();
    void destroy();
};
