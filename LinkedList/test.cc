/*
 * @Author: LIN-AC 1335954640@qq.com
 * @Date: 2022-08-14 22:21:07
 * @LastEditors: LIN-AC 1335954640@qq.com
 * @LastEditTime: 2022-08-15 17:05:41
 * @FilePath: \code\LinkedList\test.cc
 * @Description:
 *
 * Copyright (c) 2022 by LIN-AC 1335954640@qq.com, All Rights Reserved.
 */
#include <iostream>
using namespace std;
class test1
{
public:
    void test();
};
void test1::test()
{
    cout << "test1()" << endl;
}
class test2
{
public:
    virtual void test();
};
void test2::test()
{
    cout << "test2()" << endl;
}

int main()
{
    test1 t1;
    test2 t2;
    cout << sizeof(t1) << endl;
    cout << sizeof(t2) << endl;
    return 0;
}
