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
        xor_linked_list() :
        _count(0),
        _before_front(new node),
        _after_back(new node) {
            this->_before_front->_fork = this->_after_back;
            this->_after_back->_fork = this->_before_front;
        }
        xor_linked_list(std::initializer_list<t> list) : xor_linked_list() {
            for (auto const& value : list) {
                this->push_back(value);
            }
        }
        explicit xor_linked_list(size_t count, t const& value) : xor_linked_list() {
            for (int i(0); i < count; i++) {
                this->push_back(value);
            }
        }
        explicit xor_linked_list(size_t count) : xor_linked_list(count, t()) {}
        ~xor_linked_list() {
            // 할당된 노드들 할당 해제하는 로직 필요
        }
        void push_front(t const& value) {
            auto new_node(new node(value));
            auto front(this->_before_front->_fork); // nullptr^front(fork) == front
            auto after_front(this->get_node_with_xor(front->_fork, this->_before_front)); // before_node^front == after_front
            front->_fork = this->get_node_with_xor(new_node, after_front);
            new_node->_fork = this->get_node_with_xor(this->_before_front, front);
            this->_before_front->_fork = new_node;
            ++this->_count;
        }
        void pop_front() {
            auto front(this->_before_front->_fork);

            if (front != this->_after_back) { // _before_front의 다음이 _after_back인 경우 pop할 값이 없음을 의미
                auto after_front(this->get_node_with_xor(front->_fork, this->_before_front));
                auto after_after_front(this->get_node_with_xor(after_front->_fork, front));
                after_front->_fork = this->get_node_with_xor(this->_before_front, after_after_front);
                this->_before_front->_fork = after_front;
                --this->_count;
            }
        }
        void push_back(t const& value) {
            auto new_node(new node(value));
            auto back(this->_after_back->_fork);
            auto before_back(this->get_node_with_xor(back->_fork, this->_after_back));
            back->_fork = this->get_node_with_xor(before_back, new_node);
            new_node->_fork = this->get_node_with_xor(back, this->_after_back);
            this->_after_back->_fork = new_node;
            ++this->_count;
        }
        void pop_back() {
            auto back(this->_after_back->_fork);

            if (back != this->_before_front) {
                auto before_back(this->get_node_with_xor(back->_fork, this->_after_back));
                auto before_before_back(this->get_node_with_xor(before_back->_fork, back));
                before_back->_fork = this->get_node_with_xor(before_before_back, this->_after_back);
                this->_after_back->_fork = before_back;
                --this->_count;
            }
        }
        t& operator[](size_t index) const {
            if (this->_count == 0) {
                throw std::out_of_range("Unable to access element of index.");
            }

            int count(0);
            node* before_front(this->_before_front);
            node* front(this->_before_front->_fork);

            while (count < index) {
                node* temp(front);
                front = this->get_node_with_xor(front->_fork, before_front);
                before_front = temp;
                ++count;
            }

            return front->_value;
        }
        t front() const { return this->_before_front->_fork != this->_after_back ? this->_before_front->_fork->_value : t(); }
        t back() const { return this->_after_back->_fork != this->_before_front ? this->_after_back->_fork->_value : t(); }
        size_t count() const { return this->_count; };
    };

    template class xor_linked_list<int>;
}