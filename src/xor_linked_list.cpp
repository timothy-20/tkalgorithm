//
// Created by jungu on 4/9/2023.
//

#include <xor_linked_list.h>

namespace tk {
    template <typename t>
    typename xor_linked_list<t>::node* xor_linked_list<t>::get_node_with_xor(node const* lhs, node const* rhs) const { // prev와 next에 해당하는 노드를 받음
        return reinterpret_cast<node*>(reinterpret_cast<uintptr_t>(lhs) ^ reinterpret_cast<uintptr_t>(rhs)); // uintptr 타입으로 xor 연산 포인터 값으로 형 변환
    }

    template <typename t>
    xor_linked_list<t>::xor_linked_list() :
    _count(0),
    _before_front(new node),
    _after_back(new node) {
        this->_before_front->_fork = this->_after_back;
        this->_after_back->_fork = this->_before_front;
    }

    template <typename t>
    xor_linked_list<t>::xor_linked_list(std::initializer_list<t> list) : xor_linked_list() {
        for (auto const& value : list) {
            this->push_back(value);
        }
    }

    template <typename t>
    xor_linked_list<t>::xor_linked_list(size_t count, t const& value) : xor_linked_list() {
        for (int i(0); i < count; i++) {
            this->push_back(value);
        }
    }

    template <typename t>
    xor_linked_list<t>::~xor_linked_list() {
        while (this->_count != 0) {
            this->pop_back();
        }

        delete this->_before_front;
        delete this->_after_back;
    }

    template <typename t>
    void xor_linked_list<t>::push_front(t const& value) {
        auto new_node(new node(value));
        auto front(this->_before_front->_fork); // nullptr^front(fork) == front
        auto after_front(this->get_node_with_xor(front->_fork, this->_before_front)); // before_node^front == after_front
        front->_fork = this->get_node_with_xor(new_node, after_front);
        new_node->_fork = this->get_node_with_xor(this->_before_front, front);
        this->_before_front->_fork = new_node;
        ++this->_count;
    }

    template <typename t>
    void xor_linked_list<t>::pop_front() {
        auto front(this->_before_front->_fork);

        if (front != this->_after_back) { // _before_front의 다음이 _after_back인 경우 pop할 값이 없음을 의미
            auto after_front(this->get_node_with_xor(front->_fork, this->_before_front));
            auto after_after_front(this->get_node_with_xor(after_front->_fork, front));
            after_front->_fork = this->get_node_with_xor(this->_before_front, after_after_front);
            delete this->_before_front->_fork; // front node 할당 해제
            this->_before_front->_fork = after_front;
            --this->_count;
        }
    }

    template <typename t>
    void xor_linked_list<t>::push_back(t const& value) {
        auto new_node(new node(value));
        auto back(this->_after_back->_fork);
        auto before_back(this->get_node_with_xor(back->_fork, this->_after_back));
        back->_fork = this->get_node_with_xor(before_back, new_node);
        new_node->_fork = this->get_node_with_xor(back, this->_after_back);
        this->_after_back->_fork = new_node;
        ++this->_count;
    }

    template <typename t>
    void xor_linked_list<t>::pop_back() {
        auto back(this->_after_back->_fork);

        if (back != this->_before_front) {
            auto before_back(this->get_node_with_xor(back->_fork, this->_after_back));
            auto before_before_back(this->get_node_with_xor(before_back->_fork, back));
            before_back->_fork = this->get_node_with_xor(before_before_back, this->_after_back);
            delete this->_after_back->_fork; // back node 할당 해제
            this->_after_back->_fork = before_back;
            --this->_count;
        }
    }

    template <typename t>
    t& xor_linked_list<t>::operator[](size_t index) const {
        if (index >= this->_count) {
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

    template class xor_linked_list<int>;
}