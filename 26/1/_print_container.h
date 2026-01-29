#include <type_traits>
#include <utility>

template<class>
inline constexpr bool dependent_false_v = false;

#if defined(__cpp_concepts) && (__cpp_concepts >= 201907L)
//----------------------FOR C++ 20 AND HIGER-------------------------------
// 1) 是否可迭代：有 begin/end
template<class T>
concept Iterable = requires(T t)
{
    std::begin(t);
    std::end(t);
};

// 2) 是否 stack-like：empty/top/pop
template<class T>
concept StackLike = requires(T t)
{
    { t.empty() } -> std::convertible_to<bool>;
    t.top();
    t.pop();
};

// 3) 是否 queue-like：empty/front/pop
template<class T>
concept QueueLike = requires(T t)
{
    { t.empty() } -> std::convertible_to<bool>;
    t.front();
    t.pop();
};

template<Iterable C>
void print_container(const C& c)
{
    for (const auto& x : c)
        std::cout << x << " ";
    std::cout << "\n";
}

template<StackLike S>
requires (!Iterable<S>)
void print_container(S s)
{
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "\n";
}

template<QueueLike Q>
requires (!Iterable<Q> && !StackLike<Q>)
void print_container(Q q)
{
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";
}

template<class T>
requires (!Iterable<T> && !StackLike<T> && !QueueLike<T>)
void print_container(const T&)
{
    static_assert(dependent_false_v<T>,
        "print_container: type is not iterable(begin/end), not stack-like(top/pop/empty), not queue-like(front/pop/empty).");
}

#else
//----------------------FOR C++ 17 AND lOER-------------------------------
namespace detail
{
template<class...>
using void_t = void;

template<class T, class = void>
struct is_iterable : std::false_type {};
template<class T>
struct is_iterable<T, void_t<
    decltype(std::begin(std::declval<T&>())),
    decltype(std::end  (std::declval<T&>()))
>> : std::true_type {};
template<class T>
inline constexpr bool is_iterable_v = is_iterable<T>::value;

template<class T, class = void>
struct is_stacklike : std::false_type {};
template<class T>
struct is_stacklike<T, void_t<
    decltype(std::declval<T&>().empty()),
    decltype(std::declval<T&>().top()),
    decltype(std::declval<T&>().pop())
>> : std::true_type {};
template<class T>
inline constexpr bool is_stacklike_v = is_stacklike<T>::value;

template<class T, class = void>
struct is_queuelike : std::false_type {};
template<class T>
struct is_queuelike<T, void_t<
    decltype(std::declval<T&>().empty()),
    decltype(std::declval<T&>().front()),
    decltype(std::declval<T&>().pop())
>> : std::true_type {};
template<class T>
inline constexpr bool is_queuelike_v = is_queuelike<T>::value;
} // namespace detail

template<class C, std::enable_if_t<detail::is_iterable_v<C>, int> = 0>
void print_container(const C& c)
{
    for (const auto& x : c) std::cout << x << " ";
    std::cout << "\n";
}

template<class S,
         std::enable_if_t<!detail::is_iterable_v<S> && detail::is_stacklike_v<S>, int> = 0>
void print_container(S s)
{
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "\n";
}

template<class Q,
         std::enable_if_t<!detail::is_iterable_v<Q> && !detail::is_stacklike_v<Q> && detail::is_queuelike_v<Q>, int> = 0>
void print_container(Q q)
{
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";
}

template<class T,
         std::enable_if_t<!detail::is_iterable_v<T> && !detail::is_stacklike_v<T> && !detail::is_queuelike_v<T>, int> = 0>
void print_container(const T&)
{
    static_assert(dependent_false_v<T>,
        "print_container: type is not iterable(begin/end), not stack-like(top/pop/empty), not queue-like(front/pop/empty).");
}
#endif
