#pragma once
#include"_my_link_list.h"

namespace MTL_A
{

template<typename T>
class Queue
{

public:
    void push(const T& x)
    {
        list.push_back(x);
    }

    bool pop()
    {
        return list.pop_front();
    }

    T& front()
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
