/*
 * @Author: LIN-AC 1335954640@qq.com
 * @Date: 2022-08-10 17:30:03
 * @LastEditors: LIN-AC 1335954640@qq.com
 * @LastEditTime: 2022-08-17 20:22:55
 * @FilePath: \code\mystring\cow.cc
 * @Description:string cow实现
 *
 * Copyright (c) 2022 by LIN-AC 1335954640@qq.com, All Rights Reserved.
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
class String;

class String
{
private:
    char *pstr_;

public:
    String()
        : pstr_(new char[5]() + 4) //前四位存放计数器，最后一位存放'\0'
    {
        cout << "String()" << endl;
        init_count();
    }
    String(const char *str)
        : pstr_(new char[strlen(str) + 5] + 4)
    {
        strcpy(pstr_, str);
    }
    explicit String(const String &str)
    { //浅拷贝，只修改指针
        pstr_ = str.pstr_;
        auto_increase();
    }
    String(String &&str) noexcept
        : pstr_(nullptr)
    {
        cout << "String(String &&str)" << endl;
        pstr_ = str.pstr_;
        auto_increase();
    }
    String &operator=(const char *str)
    {
        if (strcmp(pstr_, str) == 0)
            return *this;
        destroy();
        pstr_ = new char[strlen(str) + 5] + 4;
        init_count();
        strcpy(pstr_, str);
    }
    String &operator=(String &&str) noexcept
    {
        cout << "String &operator=(String &&str)" << endl;

        if (this != &str)
        {
            destroy();
            pstr_ = str.pstr_;
            auto_increase();
        }
        return *this;
    }
    String &operator=(const String &str)
    {
        if (pstr_ != str.pstr_)
        {
            destroy();
            pstr_ = str.pstr_;
            auto_increase();
        }
    }
    ~String()
    {
        destroy();
    }

    char &operator[](size_t idx)
    {
        if (idx >= 0 && idx < size())
        {
            if (get_count() > 1)
            {
                char *temp = new char(size() + 5) + 4;
                strcpy(temp, pstr_);
                destroy();
                pstr_ = temp;
                init_count();
            }
            return pstr_[idx];
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const String &rhs)
    {
        os << rhs.pstr_;
        return os;
    }

public:
    //获取计数
    int get_count()
    {
        return *(int *)(pstr_ - 4);
    }
    //转c风格字符串
    const char *c_str()
    {
        return pstr_;
    }
    //字符串大小
    size_t size()
    {
        return strlen(pstr_);
    }

private:
    //初始化计数器
    void init_count()
    {
        //初始化计数器为1
        *(int *)(pstr_ - 4) = 1;
    }

    //计数器自增
    void auto_increase()
    {
        ++*(int *)(pstr_ - 4);
    }

    //计数器自减
    void auto_decrease()
    {
        --*(int *)(pstr_ - 4);
    }
    //销毁
    void destroy()
    {
        auto_decrease();
        if (!((int *)(pstr_ - 4)))
        {
            delete[](pstr_ - 4);
        }
    }
};
int main()
{
    String str1 = "hello";

    String str2("test");
    cout << str2 << endl;
    String str3("world");
    String str4(move(str3));
    cout << str3 << endl;
    str1 = move(str2);

    cout << str1 << endl;

    return 0;
}