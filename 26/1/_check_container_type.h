#pragma once
#include <type_traits>
#include <utility>
#include <iterator>
#include <concepts>

//#ifndef __cplusplus >= 202002L
//#else
//#endif



//----------------------FOR C++ 20 AND LATER-------------------------------
namespace ct   // container tools
{

template<class>
inline constexpr bool dependent_false_v = false;

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

template<class T>
concept QueueLike = requires(T t)
{
    { t.empty() } -> std::convertible_to<bool>;
    t.front();
    t.pop();
};


}
