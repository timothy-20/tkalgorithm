//
// Created by jungu on 3/21/2023.
//

#pragma once
#include <iostream>

namespace tk {
    template <typename t>
    class dynamic_array {
    private:
        size_t _capacity;
        size_t _count;
        t* _list;

    private:
        static t* reallocate(t *list, size_t capacity);
        void grow_capacity();
        void shrink_capacity();

    public:
        template <typename it>
        class iterator {
        private:
            dynamic_array<it> _list;

        public:
            using value_type = it;
            using pointer_type = it*;
            using reference_type = it&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;

            explicit iterator(dynamic_array const& list) : _list(list) {}
//            reference_type operator*() const { return }
//            pointer_type operator->() const { return }
        };

        template <typename rit>
        class reverse_iterator : public iterator<rit> {
            friend class dynamic_array<t>;

        private:

        public:
        };

    public:
        dynamic_array(std::initializer_list<t> list) :
        _capacity(list.size() > 0 ? list.size() * 2 : 10),
        _count(0),
        _list(new t[this->_capacity]) {
            for (auto const& value : list) {
                this->push_back(value);
            }
        }
        dynamic_array(size_t count, const t& value) :
        _capacity(count > 0 ? count * 2 : 10),
        _count(0),
        _list(new t[this->_capacity]) {
            for (int i(0); i < count; i++) {
                this->push_back(value);
            }
        }
        dynamic_array(size_t count) : dynamic_array(count, 0) {}
        dynamic_array() : dynamic_array(0) {}
        ~dynamic_array() { delete[] this->_list; }
        void push_back(t value);
        void pop_back();
        void insert(t value, size_t index);
        void remove(size_t index);
        t& operator[] (size_t index); // throwable
        size_t count() const { return this->_count; }
        size_t capacity() const { return this->_capacity; }
    };
}