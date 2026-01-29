#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include <type_traits>
#include <utility>

template<class>
inline constexpr bool dependent_false_v = false;

#ifndef CPP20_OR_LATER

template<class T>
concept Iterable = requires(T t)
{
    std::begin(t);
    std::end(t);
};

template<class T>
concept StackLike = requires(T t)
{
    { t.empty() } -> std::convertible_to<bool>;
    t.top();
    t.pop();
};

template<class T,typename V>
concept QueueLike = requires(T t)
{
    { t.empty() } -> std::convertible_to<bool>;
    t.front();
    t.pop();
};

template<Iterable C,typename V>
void remove_from_container(C& c,const T& target)
{
    for(auto &iter: c)
    {
        if(iter==target)

    }
}

template<StackLike S,typename V>
requires (!Iterable<S>)
void remove_from_container(S& s,const T& target)
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

template<QueueLike Q>
requires (!Iterable<Q> && !StackLike<Q>)
void remove_from_container(Q& q,const T& target)
{
    while (!q.empty())
    {
        if (q.front() == target)
        {
            q.pop();
            break;
        }
        s.pop();
    }
}

template<class T>
requires (!Iterable<T> && !StackLike<T> && !QueueLike<T>)
void remove_from_container(const T&)
{
    static_assert(dependent_false_v<T>,
        "remove_from_container: type is not iterable(begin/end), not stack-like(top/pop/empty), not queue-like(front/pop/empty).");
}

#else



#endif
