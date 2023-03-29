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
            dynamic_array<it>* _list;
            size_t _index;

        public:
            using value_type = it;
            using pointer_type = it*;
            using reference_type = it&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;

            explicit iterator(dynamic_array<it>*list, size_t index = 0) :
            _list(list),
            _index(index) {}
            reference_type operator*() const {
                if (this->_list == nullptr) {
                    throw std::out_of_range("Unable to access dynamic array element with reference.");
                }

                return this->_list[this->_index];
            }

            pointer_type operator->() const {
                if (this->_list == nullptr) {
                    throw std::out_of_range("Unable to access dynamic array element with pointer.");
                }

                return &this->_list[this->_index];
            }

            virtual iterator operator+(size_t size) {
                if (this->_list.count() <= this->_index + size) {
                    return iterator(nullptr);
                }

                return iterator(this->_list, this->_index + size);
            }

            virtual iterator& operator++() {
                if (this->_index < this->_list.count()) {
                    this->_index++;
                }

                return *this;
            }

            virtual iterator operator++(value_type) {
                iterator temp_iterator(*this);

                if (this->_index < this->_list.count()) {
                    this->_index++;
                }

                return temp_iterator;
            }

            virtual iterator operator-(size_t size) {
                if (this->_index - size < 0) {
                    return iterator(nullptr);
                }

                return iterator(this->_list, this->_index - size);
            }

            virtual iterator& operator--() {
                if (this->_index >= 0) {
                    this->_index--;
                }

                return *this;
            }

            virtual iterator operator--(value_type) {
                iterator temp_iterator(*this);

                if (this->_index >= 0) {
                    this->_index--;
                }

                return temp_iterator;
            }
            bool operator==(iterator const& other) const { return this->_list == other._list && this->_index == other._index; }
            bool operator!=(iterator const& other) const { return this->_list != other._list || this->_index != other._index; }

            // 추가적인 operator들을 지원할 계획입니다.
        };

        template <typename rit>
        class reverse_iterator : public iterator<rit> {
            friend class dynamic_array<t>;

        public:
            reverse_iterator(iterator<rit> const& other) : iterator<rit>(other) {}
            iterator<rit> operator+(size_t size) override {

            }

            iterator<rit>& operator++() override {

            }

            iterator<rit> operator++(iterator<rit>::value_type) override {

            }
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
        t front() const {
            if (this->_count == 0) {
                throw std::out_of_range("Unable to access front of dynamic array.");
            }

            return this->_list[0];
        }
        t back() const {
            if (this->_count == 0) {
                throw std::out_of_range("Unable to access back of dynamic array.");
            }

            return this->_list[this->_count - 1];
        }
        size_t count() const { return this->_count; }
        size_t capacity() const { return this->_capacity; }
    };
}