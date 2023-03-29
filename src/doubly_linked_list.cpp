//
// Created by 임정운 on 2023/03/29.
//

#include <doubly_linked_list.h>

namespace tk {
    // iterator implementation
    template <typename t>
    template <typename it>
    it& doubly_linked_list<t>::iterator<it>::operator*() {
        if (this->_cursor == nullptr) {
            throw std::out_of_range("Unable to access pointer. out of range of array.");
        }

        return this->_cursor->_value;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it> doubly_linked_list<t>::iterator<it>::operator+(size_t size) {
        auto temp_cursor(this->_cursor);
        size_t count(0);

        while (temp_cursor) {
            if (count == size) {
                break;
            }

            temp_cursor = temp_cursor->_next;
            count++;
        }

        return iterator(temp_cursor);
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it>& doubly_linked_list<t>::iterator<it>::operator++() {
        if (this->_cursor) {
            this->_cursor = this->_cursor->_next;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it> doubly_linked_list<t>::iterator<it>::operator++(it) {
        auto temp_iterator(*this);

        if (this->_cursor) {
            this->_cursor = this->_cursor->_next;
        }

        return temp_iterator;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it> doubly_linked_list<t>::iterator<it>::operator-(size_t size) {
        auto temp_cursor(this->_cursor);
        size_t count(0);

        while (temp_cursor) {
            if (count == size) {
                break;
            }

            temp_cursor = temp_cursor->_prev;
            count++;
        }

        return iterator(temp_cursor);
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it>& doubly_linked_list<t>::iterator<it>::operator--() {
        if (this->_cursor) {
            this->_cursor = this->_cursor->_prev;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename doubly_linked_list<t>::template iterator<it> doubly_linked_list<t>::iterator<it>::operator--(it) {
        auto temp_iterator(*this);

        if (this->_cursor) {
            this->_cursor = this->_cursor->_prev;
        }

        return temp_iterator;
    }

    // reverse iterator implementation
    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit> doubly_linked_list<t>::reverse_iterator<rit>::operator+(size_t size) {
        return iterator<rit>::operator-(size);
    }

    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit>& doubly_linked_list<t>::reverse_iterator<rit>::operator++() {
        *this = iterator<rit>::operator--();

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit> doubly_linked_list<t>::reverse_iterator<rit>::operator++(typename doubly_linked_list<t>::iterator<rit>::value_type) {
        iterator<rit>::operator--(rit());

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename doubly_linked_list<t>::template iterator<rit> doubly_linked_list<t>::reverse_iterator<rit>::operator-(size_t size) {
        return iterator<rit>::operator+(size);
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
        iterator<rit>::operator++(rit());

        return *this;
    }

    // doubly linked list implementation
    template <typename t>
    void doubly_linked_list<t>::push_front(t const& value) {
        auto new_node(std::make_shared<node>(value));

        if (this->_front == nullptr) {
            this->_front = new_node;
            this->_back = new_node;

        } else {
            new_node->_next = this->_front;
            this->_front->_prev = new_node;
            this->_front = new_node;
        }

        this->_count++;
    }

    template <typename t>
    void doubly_linked_list<t>::pop_front() {
        if (this->_front == nullptr) {
            return;
        }

        if (this->_front == this->_back) {
            this->_front = nullptr;
            this->_back = nullptr;

        } else {
            this->_front = this->_front->_next;
            this->_front->_prev = nullptr;
        }

        this->_count--;
    }

    template <typename t>
    void doubly_linked_list<t>::push_back(t const& value) {
        auto new_node(std::make_shared<node>(value));

        if (this->_front == nullptr) {
            this->_front = new_node;
            this->_back = new_node;

        } else {
            new_node->_prev = this->_back;
            this->_back->_next = new_node;
            this->_back = new_node;
        }

        this->_count++;
    }

    template <typename t>
    void doubly_linked_list<t>::pop_back() {
        if (this->_back == nullptr) {
            return;
        }

        if (this->_back == this->_front) {
            this->_front = nullptr;
            this->_back = nullptr;

        } else {
            this->_back = this->_back->_prev;
            this->_back->_next = nullptr;
        }

        this->_count--;
    }

    template <typename t>
    void doubly_linked_list<t>::insert(const_iterator_type iterator, t const& value) {
        if (iterator == this->cend()) {
            throw std::out_of_range("Unable to insert node to doubly linked list. out of range of array.");
        }

        auto prev_node(iterator._cursor->_prev);
        auto new_node(std::make_shared<node>(value));
        new_node->_next = iterator._cursor;
        iterator._cursor->_prev = new_node;
        new_node->_prev = prev_node;
        prev_node->_next = new_node;
        this->_count++;
    }

    template <typename t>
    void doubly_linked_list<t>::remove(const_iterator_type iterator) {
        if (iterator == this->cend()) {
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
        if (iterator == this->end()) {
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
