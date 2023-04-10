//
// Created by 임정운 on 2023/04/05.
//

#pragma once
#include <iostream>

namespace tk {
    template <typename t>
    class xor_linked_list {
    private:
        struct node {
            t _value;
            node* _fork; // 이전 노드와 이후 노드를 xor 연산한 값에 대한 포인터 노드.

            explicit node(t const& value) :
                    _value(value),
                    _fork(nullptr) {}
            node() : node(t()) {}
        };

    private:
        size_t _count;
        node* _before_front;
        node* _after_back;

        node* get_node_with_xor(node const* lhs, node const* rhs) const;

    public:
        xor_linked_list();
        xor_linked_list(std::initializer_list<t> list);
        explicit xor_linked_list(size_t count, t const& value);
        explicit xor_linked_list(size_t count) : xor_linked_list(count, t()) {}
        ~xor_linked_list();
        void push_front(t const& value);
        void pop_front();
        void push_back(t const& value);
        void pop_back();
        t& operator[](size_t index) const;
        t front() const { return this->_before_front->_fork != this->_after_back ? this->_before_front->_fork->_value : t(); }
        t back() const { return this->_after_back->_fork != this->_before_front ? this->_after_back->_fork->_value : t(); }
        size_t count() const { return this->_count; };
    };
}