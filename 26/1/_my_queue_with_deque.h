#pragma once
#include"_my_deque.h"

namespace MTL_A
{

template<class T>
class Queue_D
{
private:
    Deque<T> dq;

public:
    void push(const T& x)
    {
        dq.push_back(x);
    }

    bool pop()
    {
        return dq.pop_front();
    }

    T& front()
    {
        return dq.front();
    }

    const T& front() const
    {
        return dq.front();
    }

    bool empty() const
    {
        return dq.empty();
    }
};

}
