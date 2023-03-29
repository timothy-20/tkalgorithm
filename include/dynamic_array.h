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
            dynamic_array* _list;
            int64_t _index;

        public:
            using value_type = it;
            using pointer_type = it*;
            using reference_type = it&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;

            explicit iterator(dynamic_array* list, int64_t const& index = 0) :
            _list(list),
            _index(index) {}
            reference_type operator*() const;
            pointer_type operator->() const;
            virtual iterator operator+(size_t size);
            virtual iterator& operator+=(size_t size);
            virtual iterator& operator++();
            virtual iterator operator++(value_type);
            virtual iterator operator-(size_t size);
            virtual iterator& operator-=(size_t size);
            virtual iterator& operator--();
            virtual iterator operator--(value_type);
            bool operator==(iterator const& other) const { return this->_list == other._list && this->_index == other._index; }
            bool operator!=(iterator const& other) const { return this->_list != other._list || this->_index != other._index; }
            bool operator<(iterator const& other) const { return this->_list == other._list && this->_index < other._index; }
            bool operator<=(iterator const& other) const { return this->_list == other._list && this->_index <= other._index; }
            bool operator>(iterator const& other) const { return this->_list == other._list && this->_index > other._index; }
            bool operator>=(iterator const& other) const { return this->_list == other._list && this->_index >= other._index; }
        };

        template <typename rit>
        class reverse_iterator : public iterator<rit> {
        public:
            reverse_iterator(iterator<rit> const& other) : iterator<rit>(other) {}
            iterator<rit> operator+(size_t size) override;
            iterator<rit>& operator+=(size_t size) override;
            iterator<rit>& operator++() override;
            iterator<rit> operator++(typename iterator<rit>::value_type) override;
            iterator<rit> operator-(size_t size) override;
            iterator<rit>& operator-=(size_t size) override;
            iterator<rit>& operator--() override;
            iterator<rit> operator--(typename iterator<rit>::value_type) override;
        };

    public:
        using iterator_type = iterator<t>;
        using const_iterator_type = iterator<t const>;
        using reverse_iterator_type = reverse_iterator<t>;
        using const_reverse_iterator_type = reverse_iterator<t const>;

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
        void insert(const_iterator_type iterator, t const& value);
        void remove(const_iterator_type iterator);
        void resize(size_t size, t const& value = t());
        t& operator[] (size_t index);
        t front() const;
        t back() const;
        size_t count() const { return this->_count; }
        size_t capacity() const { return this->_capacity; }
        iterator_type begin() { return iterator<t>(this); }
        const_iterator_type cbegin() { return iterator<t const>(this); }
        reverse_iterator_type rbegin() { return iterator<t>(this, this->_count - 1); }
        const_reverse_iterator_type crbegin() { return iterator<t const>(this, this->_count - 1); }
        iterator_type end() { return iterator<t>(nullptr, this->_count); }
        const_iterator_type cend() { return iterator<t const>(nullptr, this->_count); }
        reverse_iterator_type rend() { return iterator<t>(nullptr, -1); }
        const_reverse_iterator_type crend() { return iterator<t const>(nullptr, -1); }
    };
}