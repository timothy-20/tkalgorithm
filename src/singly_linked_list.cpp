//
// Created by jungu on 3/26/2023.
//

#include <singly_linked_list.h>

namespace tk {
    // iterator implement
    template <typename t>
    template <typename it>
    it& singly_linked_list<t>::iterator<it>::operator*() {
        if (this->_cursor == nullptr) {
            throw std::runtime_error("Unable to access singly linked list element with reference.");
        }

        return this->_cursor->_value;
    }

    template <typename t>
    template <typename it>
    it* singly_linked_list<t>::iterator<it>::operator->() {
        if (this->_cursor == nullptr) {
            throw std::runtime_error("Unable to access singly linked list element with pointer.");
        }

        return &this->_cursor->_value;
    }

    template <typename t>
    template <typename it>
    typename singly_linked_list<t>::template iterator<it>& singly_linked_list<t>::iterator<it>::operator++() {
        if (this->_cursor) {
            this->_cursor = this->_cursor->_next.get();
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename singly_linked_list<t>::template iterator<it> singly_linked_list<t>::iterator<it>::operator++(it) {
        iterator temp(*this);

        if (this->_cursor) {
            this->_cursor = this->_cursor->_next.get();
        }

        return temp;
    }

    // singly linked list implement
    template <typename t>
    void singly_linked_list<t>::push_front(t const& value) {
        auto new_node(std::make_unique<node>(value));
        new_node->_next = std::move(this->_before_front->_next);
        this->_before_front->_next = std::move(new_node);
        this->_count++;
    }

    template <typename t>
    void singly_linked_list<t>::pop_front() {
        if (this->_before_front->_next) {
            this->_before_front->_next = std::move(this->_before_front->_next->_next);
            this->_count--;
        }
    }

    template <typename t>
    void singly_linked_list<t>::assign(singly_linked_list<t>::iterator<t> iterator, t const& value) {
        if (iterator == this->end()) {
            throw std::out_of_range("Unable to assign, target node is nullptr.");
        }

        *iterator = value;
    }

    template <typename t>
    void singly_linked_list<t>::insert_after(singly_linked_list<t>::iterator<t const> iterator, t const& value) {
        if (iterator == this->cend()) {
            throw std::out_of_range("Unable to insert, target node is nullptr.");
        }

        auto next_node(std::move(iterator._cursor->_next));
        auto new_node(std::make_unique<node>(value));
        new_node->_next = std::move(next_node);
        iterator._cursor->_next = std::move(new_node);
        this->_count++;
    }

    template <typename t>
    void singly_linked_list<t>::remove_after(singly_linked_list<t>::iterator<t const> iterator) {
        if (iterator == this->cend()) {
            throw std::out_of_range("Unable to remove, target node is nullptr.");
        }
        auto next_node(std::move(iterator._cursor->_next));

        if (next_node) {
            iterator._cursor->_next = std::move(next_node->_next);
            this->_count--;
        }
    }

    template class singly_linked_list<int>::iterator<int>;
    template class singly_linked_list<int>::iterator<int const>;
    template class singly_linked_list<int>;
}