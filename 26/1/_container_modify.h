#pragma once
#include <type_traits>
#include <utility>

#include"_check_container_type.h"

// #ifndef CPP20_OR_LATER
// #else
// #endif

namespace ct // container tools
{

template<Iterable C,typename T>
void remove_from_container(C& c,const T& target)
{
    for(auto &iter: c)
    {
        //if(iter==target)

    }
}

template<StackLike S,typename T>
requires (!Iterable<S>)
void pop_until_removed(S& s,const T& target)
{
    while (!s.empty())
    {
        if (s.top() == target)
        {
            s.pop();
            break;
        }
        s.pop();
    }
}

template<QueueLike Q,typename T>
requires (!Iterable<Q> && !StackLike<Q>)
void pop_until_removed(Q& q,const T& target)
{
    while (!q.empty())
    {
        if (q.front() == target)
        {
            q.pop();
            break;
        }
        q.pop();
    }
}

template<class T>
requires (!Iterable<T> && !StackLike<T> && !QueueLike<T>)
void pop_until_removed(const T&)
{
    static_assert(dependent_false_v<T>,
        "pop_until_removed: type is not stack-like(top/pop/empty), not queue-like(front/pop/empty).");
}


}
