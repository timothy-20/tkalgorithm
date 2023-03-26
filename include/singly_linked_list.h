//
// Created by aircuve on 2023-03-23.
//

#pragma once
#include <iostream>
#include <memory>

namespace tk {
    template<typename t>
    class singly_linked_list {
    private:
        struct node;

    private:
        std::unique_ptr<node> _front;
        size_t _count;

    public:
        class iterator;

    public:
        explicit singly_linked_list() :
        _front(nullptr),
        _count(0) {}
        ~singly_linked_list() = default;
        void add_front(const t& value);
        void remove_front();
        void insert_after(iterator iterator, const t& value);
        void insert_after(uint32_t index, const t& value);
        void remove_after(iterator iterator);
        void remove_after(uint32_t index);
        t front() const { return this->_front ? this->_front->_value : t(); }
        size_t count() const { return this->_count; }
        iterator begin() const { return iterator(this->_front.get()); }
        iterator end() const { return iterator(nullptr); }
    };
}