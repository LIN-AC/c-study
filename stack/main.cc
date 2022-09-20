#include <iostream>
#include "mystack.hh"

int main()
{
    int res;
    Stack<int> items;
    items.push(0);
    items.push(1);
    items.push(2);
    items.push(3);
    items.push(4);
    items.push(5);
    items.pop(res);
    items.push(0);

    return 0;
}