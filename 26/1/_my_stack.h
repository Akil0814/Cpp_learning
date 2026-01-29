#pragma once
#include<iostream>
#include"_my_link_list.h"

namespace MTL_A
{

template <class T>
class Stack
{
public:
    Stack()= default;
    ~Stack()
    {
        list.clear();
    }

    void push(const T& x)
    {
        list.push_front(x);
    }

    bool pop()
    {
        return list.pop_front();
    }

    T& top()
    {
        return list.front();
    }

    bool empty() const
    {
        return list.empty();
    }

private:
    MTL_A::LinkedList<T> list;
};

}
