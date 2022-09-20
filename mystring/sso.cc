/*
 * @Author: LIN-AC 1335954640@qq.com
 * @Date: 2022-08-10 21:20:16
 * @LastEditors: LIN-AC 1335954640@qq.com
 * @LastEditTime: 2022-08-10 22:27:32
 * @FilePath: \code\mystring\sso.cc
 * @Description:
 *
 * Copyright (c) 2022 by LIN-AC 1335954640@qq.com, All Rights Reserved.
 */
#include <string.h>
#include <iostream>

using namespace std;

#define STRINGSIZE 24

class String
{
private:
    char *pstr_;

public:
    String()
    {
        pstr_ = new char(5) + 4;
        init_count();
    }
    String(const char *str)
    {
        pstr_ = new char(strlen(str) + 5) + 4;
        strcpy(pstr_, str);
        init_count();
    }
    String(const String &str)
    {
        if (strlen(str.pstr_) < (int)STRINGSIZE)
        {
            pstr_ = new char(strlen(str.pstr_ + 5)) + 4;
            strcpy(pstr_, str.pstr_);
            init_count();
        }
        else
        {
            pstr_ = str.pstr_;
            auto_increase();
        }
    }
    ~String()
    {
        destroy();
    }

    String &operator=(const String &str)
    {
        if (pstr_ != str.pstr_)
        {
            destroy();
            if (strlen(str.pstr_) < STRINGSIZE)
            {
                pstr_ = new char(strlen(str.pstr_ + 5)) + 4;
                strcpy(pstr_, str.pstr_);
                init_count();
            }
            else
            {
                pstr_ = str.pstr_;
                auto_increase();
            }
        }
        return *this;
    }
    String &operator=(const char *str)
    {
        if (strcmp(pstr_, str) == 0)
            return *this;
        destroy();
        pstr_ = new char(strlen(str) + 5) + 4;
        strcpy(pstr_, str);
        init_count();
        return *this;
    }
    friend ostream &operator<<(ostream &os, const String &str)
    {
        os << str.pstr_;
        return os;
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

public:
    void init_count()
    {
        *(int *)(pstr_ - 4) = 1;
    }
    void auto_increase()
    {
        ++*(int *)(pstr_ - 4);
    }
    void auto_decrease()
    {
        --*(int *)(pstr_ - 4);
    }
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
    void destroy()
    {
        auto_decrease();
        if (get_count() == 0)
        {
            if (pstr_)
            {
                delete[](pstr_ - 4);
                cout << "destroy()" << endl;
            }
        }
        pstr_ = nullptr;
    }
};
int main()
{
    String str1("hello");
    cout << str1 << endl;

    String str2(str1);
    cout << str2 << endl;
    String str3("hello");
    cout << str3 << endl;
    str1 = "testasdasdasdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    cout << str1 << endl;

    str3 = str1;
    cout << str3 << endl;

    String str4("world");
    cout << str4 << endl;
    return 0;
}