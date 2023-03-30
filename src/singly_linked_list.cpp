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
    singly_linked_list<t>::singly_linked_list(std::initializer_list<t> list) :
    _before_front(std::make_unique<node>()),
    _back(nullptr),
    _count(0) {
        for (auto iterator(std::rbegin(list)); iterator != std::rend(list); iterator++) {
            this->push_front(*iterator);
        }
    }

    template <typename t>
    singly_linked_list<t>::singly_linked_list(size_t count, const t &value) :
    _before_front(std::make_unique<node>()),
    _back(nullptr),
    _count(0) {
        for (int i(0); i < count; i++) {
            this->push_front(value);
        }
    }

    template <typename t>
    void singly_linked_list<t>::push_front(t const& value) {
        auto new_node(std::make_unique<node>(value));
        new_node->_next = std::move(this->_before_front->_next);
        this->_before_front->_next = std::move(new_node);

        if (this->_count == 0) {
            this->_back = this->_before_front->_next.get();
        }

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
    void singly_linked_list<t>::insert_after(singly_linked_list<t>::iterator<t const> iterator, t const& value) {
        if (iterator == this->cend()) {
            throw std::out_of_range("Unable to insert, target node is nullptr.");
        }

        auto next_node(std::move(iterator._cursor->_next));
        auto new_node(std::make_unique<node>(value));
        new_node->_next = std::move(next_node);

        if (next_node == nullptr) {
            this->_back = new_node.get();
        }

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

    template <typename t>
    void singly_linked_list<t>::assign(singly_linked_list<t>::iterator<t> iterator, t const& value) {
        if (iterator == this->end()) {
            throw std::out_of_range("Unable to assign, target node is nullptr.");
        }

        *iterator = value;
    }

    template <typename t>
    void singly_linked_list<t>::resize(size_t size, t const& value) {
        if (size > this->_count) {
            size_t distance(size > this->_count ? size - this->_count : this->_count - size);
            singly_linked_list new_list(distance, value);

            if (this->_count > distance) {
                this->_back->_next = std::move(new_list._before_front->_next);
                this->_back = new_list._back;

            } else {
                auto current(this->begin());
                iterator_type prev(nullptr);

                do {
                    current++;
                    prev = current;

                } while (++prev != this->end());

                current._cursor->_next = std::move(new_list._before_front->_next);
            }

        } else if (size < this->_count) {
            auto current(this->begin());

            for (int i(0); i < size; i++) {
                current++;
            }

            current._cursor->_next = nullptr;
        }

        this->_count = size;
    }

    template class singly_linked_list<int>::iterator<int>;
    template class singly_linked_list<int>::iterator<int const>;
    template class singly_linked_list<int>;
}