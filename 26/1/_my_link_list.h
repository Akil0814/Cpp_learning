#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace MTL_A
{

template<typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
        Node(const T& v) : data(v), prev(nullptr), next(nullptr) {}
        Node(T&& v) : data(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

public:
    LinkedList() = default;

    LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), size_(0)
    {
        Node* cur = other.head_;
        while (cur)
        {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    LinkedList& operator=(const LinkedList& other)
    {
        if (this == &other)
            return *this;
        clear();
        Node* cur = other.head_;
        while (cur)
        {
            push_back(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    ~LinkedList()
    {
        clear();
    }

    bool empty() const noexcept
    {
        return size_ == 0;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    T& front()
    {
        if (empty())
            throw std::runtime_error("LinkedList::front on empty list");
        return head_->data;
    }

    const T& front() const
    {
        if (empty())
            throw std::runtime_error("LinkedList::front on empty list");
        return head_->data;
    }

    T& back()
    {
        if (empty())
            throw std::runtime_error("LinkedList::back on empty list");
        return tail_->data;
    }

    const T& back() const
    {
        if (empty())
            throw std::runtime_error("LinkedList::back on empty list");
        return tail_->data;
    }

    void push_front(const T& value)
    {
        Node* n = new Node(value);
        n->next = head_;
        if (head_)
            head_->prev = n;

        head_ = n;

        if (!tail_)
            tail_ = n;

        ++size_;
    }

    void push_front(T&& value)
    {
        Node* n = new Node(std::move(value));
        n->next = head_;
        if (head_)
            head_->prev = n;

        head_ = n;

        if (!tail_)
            tail_ = n;

        ++size_;
    }

    void push_back(const T& value)
    {
        Node* n = new Node(value);
        n->prev = tail_;
        if (tail_)
            tail_->next = n;
        tail_ = n;

        if (!head_)
            head_ = n;

        ++size_;
    }

    void push_back(T&& value)
    {
        Node* n = new Node(std::move(value));
        n->prev = tail_;
        if (tail_)
            tail_->next = n;
        tail_ = n;

        if (!head_)
            head_ = n;

        ++size_;
    }

    bool pop_front()
    {
        if (empty())
            return false;

        Node* victim = head_;
        head_ = head_->next;
        if (head_)
            head_->prev = nullptr;
        else
            tail_ = nullptr;

        delete victim;
        --size_;

        return true;
    }

    bool pop_back()
    {
        if (empty())
            return false;

        Node* victim = tail_;
        tail_ = tail_->prev;
        if (tail_)
            tail_->next = nullptr;
        else
            head_ = nullptr;

        delete victim;
        --size_;

        return true;
    }

    void clear() noexcept
    {
        Node* cur = head_;
        while (cur)
        {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void print(std::ostream& os = std::cout) const
    {
        Node* cur = head_;
        while (cur) {
            os << cur->data;
            if (cur->next) os << " -> ";
            cur = cur->next;
        }
        os << "\n";
    }
};


}
