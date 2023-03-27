//
// Created by jungu on 3/26/2023.
//

#include <singly_linked_list.h>

namespace tk {
    template <typename t>
    t& singly_linked_list<t>::iterator::operator*() {
        if (this->_cursor == nullptr) {
            throw std::runtime_error("Unable to access, this pointer is nullptr.");
        }

        return this->_cursor->_value;
    }

    template <typename t>
    typename singly_linked_list<t>::iterator singly_linked_list<t>::iterator::operator+(size_t index) {
        size_t count(0);
        node* temp_node(this->_cursor);

        while (temp_node) {
            if (count == index)
                break;

            temp_node = temp_node->_next.get();
            count++;
        }

        return iterator(temp_node);
    }

    template <typename t>
    typename singly_linked_list<t>::iterator& singly_linked_list<t>::iterator::operator++() {
        if (this->_cursor) {
            this->_cursor = this->_cursor->_next.get();
        }

        return *this;
    }

    template <typename t>
    typename singly_linked_list<t>::iterator singly_linked_list<t>::iterator::operator++(t) {
        iterator temp(*this);

        if (this->_cursor) {
            this->_cursor = this->_cursor->_next.get();
        }

        return temp;
    }

    template <typename t>
    void singly_linked_list<t>::add_front(const t &value) {
        auto new_node(std::make_unique<node>(value));
        new_node->_next = std::move(this->_front);
        this->_front = std::move(new_node);
        this->_count++;
    }

    template <typename t>
    void singly_linked_list<t>::remove_front() {
        if (this->_front) {
            this->_front = std::move(this->_front->_next);
            this->_count--;
        }
    }

    template <typename t>
    void singly_linked_list<t>::assign(singly_linked_list::iterator iterator, const t &value) {
        if (iterator == this->end()) {
            throw std::out_of_range("Unable to assign, target node is nullptr.");
        }

        *iterator = value;
    }

    template <typename t>
    void singly_linked_list<t>::assign(size_t index, const t &value) {
        this->assign(this->begin() + index, value);
    }

    template <typename t>
    void singly_linked_list<t>::insert_after(singly_linked_list::iterator iterator, const t &value) {
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
    void singly_linked_list<t>::insert_after(size_t index, const t &value) {
        this->insert_after(this->begin() + index, value);
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

    template <typename t>
    void singly_linked_list<t>::remove_after(size_t index) {
        this->remove_after(this->begin() + index);
    }

    template class singly_linked_list<int>;
}