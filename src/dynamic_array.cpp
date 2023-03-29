//
// Created by aircuve on 2023-03-23.
//

#include <dynamic_array.h>

namespace tk {
    // iterator implementation
    template <typename t>
    template <typename it>
    it& dynamic_array<t>::iterator<it>::operator*() const {
        if (this->_list == nullptr) {
            throw std::out_of_range("Unable to access dynamic array element with reference.");
        }

        return this->_list->_list[this->_index];
    }

    template <typename t>
    template <typename it>
    it* dynamic_array<t>::iterator<it>::operator->() const {
        if (this->_list == nullptr) {
            throw std::out_of_range("Unable to access dynamic array element with pointer.");
        }

        return &this->_list->_list[this->_index];
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator+(size_t size) {
        size_t index(this->_index + size);

        if (index >= this->_list->_count) {
            return iterator(nullptr, this->_list->_count);
        }

        return iterator(this->_list, index);
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator+=(size_t size) {
        *this = *this + size;

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator++() {
        if (this->_index == this->_list->_count) {
            this->_list = nullptr;

        } else {
            this->_index++;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator++(it) {
        iterator temp_iterator(*this);

        if (this->_index == this->_list->count()) {
            this->_list = nullptr;

        } else {
            this->_index++;
        }

        return temp_iterator;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator-(size_t size) {
        if (this->_index - size < 0) {
            return iterator(nullptr, -1);
        }

        return iterator(this->_list, this->_index - size);
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator-=(size_t size) {
        *this = *this - size;

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator--() {
        if (this->_index < 0) {
            this->_list = nullptr;

        } else {
            this->_index--;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator--(it) {
        iterator temp_iterator(*this);

        if (this->_index < 0) {
            this->_list = nullptr;

        } else {
            this->_index--;
        }

        return temp_iterator;
    }

    // reverse iterator implementation
    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit> dynamic_array<t>::reverse_iterator<rit>::operator+(size_t size) {
        return iterator<rit>::operator-(size);
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit>& dynamic_array<t>::reverse_iterator<rit>::operator+=(size_t size) {
        *this = iterator<rit>::operator-=(size);

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit>& dynamic_array<t>::reverse_iterator<rit>::operator++() {
        *this = iterator<rit>::operator--();

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit> dynamic_array<t>::reverse_iterator<rit>::operator++(typename dynamic_array<t>::iterator<rit>::value_type) {
        return iterator<rit>::operator--(rit());
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit> dynamic_array<t>::reverse_iterator<rit>::operator-(size_t size) {
        return iterator<rit>::operator+(size);
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit>& dynamic_array<t>::reverse_iterator<rit>::operator-=(size_t size) {
        *this = iterator<rit>::operator+=(size);

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit>& dynamic_array<t>::reverse_iterator<rit>::operator--() {
        *this = iterator<rit>::operator++();

        return *this;
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit> dynamic_array<t>::reverse_iterator<rit>::operator--(typename dynamic_array<t>::iterator<rit>::value_type) {
        return iterator<rit>::operator++(rit());
    }

    // dynamic array implementation
    template <typename t>
    t* dynamic_array<t>::reallocate(t *list, size_t capacity) {
        auto new_list(new t[capacity]);

        for (int i(0); (i < capacity && &list[i] != nullptr); i++) {
            new_list[i] = list[i];
        }

        return new_list;
    }

    template <typename t>
    void dynamic_array<t>::grow_capacity() {
        this->_capacity *= 2;
        this->_list = dynamic_array<t>::reallocate(this->_list,this->_capacity);
    }

    template <typename t>
    void dynamic_array<t>::shrink_capacity() {
        this->_capacity /= 2;
        this->_list = dynamic_array<t>::reallocate(this->_list,this->_capacity);
    }

    template <typename t>
    void dynamic_array<t>::push_back(t value) {
        if (this->_count == this->_capacity) {
            this->grow_capacity();
        }

        this->_list[this->_count] = value;
        this->_count++;
    }

    template <typename t>
    void dynamic_array<t>::pop_back() {
        this->_list[this->_count] = t();
        this->_count--;

        if (this->_count <= (this->_capacity / 4)) {
            this->shrink_capacity();
        }
    }

    template <typename t>
    void dynamic_array<t>::insert(dynamic_array<t>::const_iterator_type iterator, t const& value) {
        if (this->_count == this->_capacity) {
            this->grow_capacity();
        }

        for (size_t i(this->_count); i > index; i--) {
            this->_list[i] = std::move(this->_list[i - 1]);
        }

        this->_list[index] = value;
        this->_count++;
    }

    template <typename t>
    void dynamic_array<t>::remove(dynamic_array<t>::const_iterator_type iterator) {
        for (size_t i(index); i < this->_count; i++) {
            this->_list[i] = std::move(this->_list[i + 1]);
        }

        this->_count--;

        if (this->_count <= (this->_capacity / 4)) {
            this->shrink_capacity();
        }
    }

    template <typename t>
    void dynamic_array<t>::resize(size_t size, t const& value) {
        // ...
    }

    template <typename t>
    t& dynamic_array<t>::operator[](size_t index) {
        if (index >= this->_count) {
            throw std::out_of_range("Unable to access element.");
        }

        return this->_list[index];
    }

    template <typename t>
    t dynamic_array<t>::front() const {
        if (this->_count == 0) {
            throw std::out_of_range("Unable to access front of dynamic array.");
        }

        return this->_list[0];
    }

    template <typename t>
    t dynamic_array<t>::back() const {
        if (this->_count == 0) {
            throw std::out_of_range("Unable to access back of dynamic array.");
        }

        return this->_list[this->_count - 1];
    }

    template class dynamic_array<int>::iterator<int>;
    template class dynamic_array<int>::iterator<int const>;
    template class dynamic_array<int>::reverse_iterator<int>;
    template class dynamic_array<int>::reverse_iterator<int const>;
    template class dynamic_array<int>;
}