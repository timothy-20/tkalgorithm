//
// Created by 임정운 on 2023/03/29.
//

#include <doubly_linked_list.h>

namespace tk {
    // iterator implementation
    template <typename t>
    template <typename it>
    it& doubly_linked_list<t>::iterator<it>::operator*() {
        if (this->_cursor == nullptr || !this->_cursor->_is_enable) {
            throw std::out_of_range("Unable to access doubly linked list element with reference.");
        }

        return this->_cursor->_value;
    }

    template <typename t>
    template <typename it>
    it* doubly_linked_list<t>::iterator<it>::operator->()  {
        if (this->_cursor == nullptr || !this->_cursor->_is_enable) {
            throw std::out_of_range("Unable to access doubly linked list element with pointer.");
        }

        return &this->_cursor->_value;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it>& doubly_linked_list<t>::iterator<it>::operator++() {
        if (this->_cursor && this->_cursor->_is_enable) {
            this->_cursor = this->_cursor->_next;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it> doubly_linked_list<t>::iterator<it>::operator++(it) {
        auto temp_iterator(*this);

        if (this->_cursor && this->_cursor->_is_enable) {
            this->_cursor = this->_cursor->_next;
        }

        return temp_iterator;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it>& doubly_linked_list<t>::iterator<it>::operator--() {
        if (this->_cursor && this->_cursor->_is_enable) {
            this->_cursor = this->_cursor->_prev;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it> doubly_linked_list<t>::iterator<it>::operator--(it) {
        auto temp_iterator(*this);

        if (this->_cursor && this->_cursor->_is_enable) {
            this->_cursor = this->_cursor->_prev;
        }

        return temp_iterator;
    }

    // reverse iterator implementation
    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit>& doubly_linked_list<t>::reverse_iterator<rit>::operator++() {
        *this = iterator<rit>::operator--();

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit> doubly_linked_list<t>::reverse_iterator<rit>::operator++(typename doubly_linked_list<t>::iterator<rit>::value_type) {
        return iterator<rit>::operator--(rit());
    }

    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit>& doubly_linked_list<t>::reverse_iterator<rit>::operator--() {
        *this = iterator<rit>::operator++();

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit> doubly_linked_list<t>::reverse_iterator<rit>::operator--(typename doubly_linked_list<t>::iterator<rit>::value_type) {
        return iterator<rit>::operator++(rit());
    }

    // doubly linked list implementation
    template <typename t>
    void doubly_linked_list<t>::push_front(t const& value) {
        auto new_node(std::make_shared<node>(value, true));

        if (this->_before_front->_next == nullptr) {
            this->_before_front->_next = new_node;
            new_node->_prev = this->_before_front;
            this->_after_back->_prev = new_node;
            new_node->_next = this->_after_back;

        } else {
            new_node->_next = this->_before_front->_next;
            this->_before_front->_next->_prev = new_node;
            this->_before_front->_next = new_node;
            new_node->_prev = this->_before_front;
        }

        this->_count++;
    }

    template <typename t>
    void doubly_linked_list<t>::pop_front() {
        if (this->_before_front->_next == nullptr) {
            return;
        }

        if (this->_before_front->_next == this->_after_back->_prev) {
            this->_before_front->_next = nullptr;
            this->_after_back->_prev = nullptr;

        } else {
            this->_before_front->_next = this->_before_front->_next->_next;
            this->_before_front->_next->_prev = this->_before_front;
        }

        this->_count--;
    }

    template <typename t>
    void doubly_linked_list<t>::push_back(t const& value) {
        auto new_node(std::make_shared<node>(value, true));

        if (this->_before_front->_next == nullptr) {
            this->_before_front->_next = new_node;
            new_node->_prev = this->_before_front;
            this->_after_back->_prev = new_node;
            new_node->_next = this->_after_back;

        } else {
            new_node->_prev = this->_after_back->_prev;
            this->_after_back->_prev->_next = new_node;
            this->_after_back->_prev = new_node;
            new_node->_next = this->_after_back;
        }

        this->_count++;
    }

    template <typename t>
    void doubly_linked_list<t>::pop_back() {
        if (this->_after_back->_prev == nullptr) {
            return;
        }

        if (this->_after_back->_prev == this->_before_front->_next) {
            this->_after_back->_prev = nullptr;
            this->_before_front->_next = nullptr;

        } else {
            this->_after_back->_prev = this->_after_back->_prev->_prev;
            this->_after_back->_prev->_next = this->_after_back;
        }

        this->_count--;
    }

    template <typename t>
    void doubly_linked_list<t>::insert(const_iterator_type iterator, t const& value) {
        if (iterator == this->cend()) {
            throw std::out_of_range("Unable to insert node to doubly linked list. out of range of array.");
        }

        auto prev_node(iterator._cursor->_prev);
        auto new_node(std::make_shared<node>(value, true));
        new_node->_next = iterator._cursor;
        iterator._cursor->_prev = new_node;
        new_node->_prev = prev_node;
        prev_node->_next = new_node;
        this->_count++;
    }

    template <typename t>
    void doubly_linked_list<t>::remove(const_iterator_type iterator) {
        if (iterator == this->cend() || iterator == this->crend()) {
            throw std::out_of_range("Unable to remove node to doubly linked list. out of range of array.");
        }

        auto prev_node(iterator._cursor->_prev);
        auto next_node(iterator._cursor->_next);
        prev_node->_next = next_node;
        next_node->_prev = prev_node;
        this->_count--;
    }

    template <typename t>
    void doubly_linked_list<t>::assign(iterator_type iterator, t const& value) {
        if (iterator == this->end() || iterator == this->rend()) {
            throw std::out_of_range("Unable to assign node to doubly linked list. out of range of array.");
        }

        *iterator = value;
    }

    template class doubly_linked_list<int>::iterator<int>;
    template class doubly_linked_list<int>::iterator<int const>;
    template class doubly_linked_list<int>::reverse_iterator<int>;
    template class doubly_linked_list<int>::reverse_iterator<int const>;
    template class doubly_linked_list<int>;
}
