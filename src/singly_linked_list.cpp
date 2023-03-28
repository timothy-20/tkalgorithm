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
            throw std::runtime_error("Unable to access, this pointer is nullptr.");
        }

        return this->_cursor->_value;
    }

    template <typename t>
    template <typename it>
    singly_linked_list<t>::iterator<it> singly_linked_list<t>::iterator<it>::operator+(size_t index) {
        size_t count(0);
        node<t>* temp_node(this->_cursor);

        while (temp_node) {
            if (count == index)
                break;

            temp_node = temp_node->_next.get();
            count++;
        }

        return iterator(temp_node);
    }

    template <typename t>
    template <typename it>
    singly_linked_list<t>::iterator<it>& singly_linked_list<t>::iterator<it>::operator++() {
        if (this->_cursor) {
            this->_cursor = this->_cursor->_next.get();
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    singly_linked_list<t>::iterator<it> singly_linked_list<t>::iterator<it>::operator++(it) {
        iterator temp(*this);

        if (this->_cursor) {
            this->_cursor = this->_cursor->_next.get();
        }

        return temp;
    }

    // singly linked list implement
    template <typename t>
    void singly_linked_list<t>::push_front(const t &value) {
        auto new_node(std::make_unique<node<t>>(value));
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
    void singly_linked_list<t>::assign(singly_linked_list<t>::iterator<t> iterator, const t &value) {
        if (iterator == this->end()) {
            throw std::out_of_range("Unable to assign, target node is nullptr.");
        }

        *iterator = value;
    }

    template <typename t>
    void singly_linked_list<t>::insert_after(singly_linked_list<t>::iterator<const t> iterator, const t &value) {
        if (iterator == this->end()) {
            throw std::out_of_range("Unable to insert, target node is nullptr.");
        }

        auto next_node(std::move(iterator->_next));
        auto new_node(std::make_unique<node>(value));
        new_node->_next = std::move(next_node);
        iterator->_next = std::move(new_node);
        this->_count++;
    }

    template <typename t>
    void singly_linked_list<t>::remove_after(singly_linked_list::iterator iterator) {
        if (iterator == this->end()) {
            throw std::out_of_range("Unable to remove, target node is nullptr.");
        }

        auto next_node(std::move(iterator->_next));

        if (next_node) {
            iterator->_next = std::move(next_node->_next);
            this->_count--;
        }
    }

    template class singly_linked_list<int>;
    template class singly_linked_list<int>::iterator<int>;
    template class singly_linked_list<int>::iterator<const int>;
}