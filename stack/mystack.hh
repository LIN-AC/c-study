#pragma once

template <typename Type>
class Stack
{
private:
    enum
    {
        MAX = 10
    };
    Type items_[MAX];
    int top_;

public:
    Stack();
    bool isempty();          //判空
    bool isfull();           //判满
    bool push(const Type &); //入栈
    bool pop(Type &);        //出栈
};

template <typename Type>
Stack<Type>::Stack()
{
    top_ = 0;
}

template <typename Type>
bool Stack<Type>::isempty()
{
    return top_ == 0;
}

template <typename Type>
bool Stack<Type>::isfull()
{
    return top_ == MAX;
}

template <typename Type>
bool Stack<Type>::push(const Type &item)
{
    if (top_ < MAX)
    {
        items_[top_++] = item;
        return true;
    }
    return false;
}

template <typename Type>
bool Stack<Type>::pop(Type &item)
{
    if (top_ != 0)
    {
        item = items_[--top_];
        return true;
    }
    return false;
}