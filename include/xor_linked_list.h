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

        node* get_node_with_xor(node const* lhs, node const* rhs) const { // prev와 next에 해당하는 노드를 받음
            return reinterpret_cast<node*>(reinterpret_cast<uintptr_t>(lhs) ^ reinterpret_cast<uintptr_t>(rhs)); // uintptr 타입으로 xor 연산 포인터 값으로 형 변환
        }

    public:
        xor_linked_list(std::initializer_list<t> list) :
        _count(list.size()),
        _before_front(new node),
        _after_back(new node) {
            for (auto const& value : list) {

            }
        }
        explicit xor_linked_list(size_t count, t const& value) :
        _count(count),
        _before_front(new node),
        _after_back(new node) {
            for (int i(0); i < count; i++) {

            }
        }
        explicit xor_linked_list(size_t count) : xor_linked_list(count, t()) {}
        xor_linked_list() : xor_linked_list(0) {}
        ~xor_linked_list() = default;
        void push_front(t const& value) {
            auto new_node(new node(value));

            if (this->_before_front->_fork == nullptr) {
                new_node->_fork = this->get_node_with_xor(this->_before_front, this->_after_back);
                this->_before_front->_fork = new_node;
                this->_after_back->_fork = new_node;

            } else {
                auto front(this->_before_front->_fork); // nullptr^front(fork) == front
                auto after_front(this->get_node_with_xor(front->_fork, this->_before_front)); // before_node^front == after_front
                new_node->_fork = this->get_node_with_xor(this->_before_front, front);
                front->_fork = this->get_node_with_xor(new_node, after_front);
                this->_before_front->_fork = new_node;
            }

            this->_count++;
        }
        void pop_front() {
            auto front(this->_before_front->_fork);

            if (front) {
                auto after_front(this->get_node_with_xor(front->_fork, this->_before_front));


//                after_front->_fork = this->get_node_with_xor(this->_before_front, )

                this->_before_front->_fork = this->get_node_with_xor(nullptr, after_front);

            } else {
                auto fork(this->_after_back->_fork);

                std::cout << "";
            }

            this->_count--;
        }
        void push_back(t const& value) {

        }
        void pop_back() {

        }
//        t& operator[](size_t index) {
//            return
//        }
        t front() const { return this->_before_front->_fork ? this->_before_front->_fork->_value : t(); }
        t back() const { return this->_after_back->_fork ? this->_after_back->_fork->_value : t(); }
        size_t count() const { return this->_count; };
    };

    template class xor_linked_list<int>;
}