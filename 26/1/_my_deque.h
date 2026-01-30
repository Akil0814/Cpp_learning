#pragma once
#include"_my_link_list.h"

#include <iterator>
#include <cstddef>
#include <type_traits>

namespace MTL_A
{

template<typename T>
class Deque
{
    LinkedList<T> list;
public:
    void push_front(const T& x) { list.push_front(x); }
    void push_back(const T& x)  { list.push_back(x); }
    bool pop_front() { return list.pop_front(); }
    bool pop() { return list.pop_front(); }
    bool pop_back()  { return list.pop_back(); }
    T& front() { return list.front(); }
    T& back()  { return list.back(); }
    bool empty() const { return list.empty(); }
};

}
