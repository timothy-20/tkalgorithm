//
// Created by aircuve on 2023-03-23.
//

#include <dynamic_array.h>
#include <iterator>

namespace tk {
    // iterator implementation
    template <typename t>
    template <typename it>
    it& dynamic_array<t>::iterator<it>::operator*() const {
        if (this->_index >= this->_list->_count || this->_index < 0) {
            throw std::out_of_range("Unable to access dynamic array element with reference.");
        }

        return this->_list->_list[this->_index];
    }

    template <typename t>
    template <typename it>
    it* dynamic_array<t>::iterator<it>::operator->() const {
        if (this->_index >= this->_list->_count || this->_index < 0) {
            throw std::out_of_range("Unable to access dynamic array element with pointer.");
        }

        return &this->_list->_list[this->_index];
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator+(difference_type n) const {
        size_t index(this->_index + n);

        if (index >= this->_list->_count) {
            return iterator(this->_list, this->_list->_count);
        }

        return iterator(this->_list, index);
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator+=(difference_type n) {
        *this = *this + n;

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator++() {
        this->_index++;

        if (this->_index >= this->_list->_count) {
            this->_index = this->_list->_count;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator++(it) {
        iterator temp_iterator(*this);
        this->_index++;

        if (this->_index >= this->_list->_count) {
            this->_index = this->_list->_count;
        }

        return temp_iterator;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator-(difference_type n) const {
        if (this->_index - n < 0) {
            return iterator(this->_list, -1);
        }

        return iterator(this->_list, this->_index - n);
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator-=(difference_type n) {
        *this = *this - n;

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>& dynamic_array<t>::iterator<it>::operator--() {
        this->_index--;

        if (this->_index < 0) {
            this->_index = -1;
        }

        return *this;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it> dynamic_array<t>::iterator<it>::operator--(it) {
        iterator temp_iterator(*this);
        this->_index--;

        if (this->_index < 0) {
            this->_index = -1;
        }

        return temp_iterator;
    }

    template <typename t>
    template <typename it>
    typename dynamic_array<t>::template iterator<it>::difference_type dynamic_array<t>::iterator<it>::operator-(const iterator<it> &other) const {
        return other._index - this->_index;
    }

    // reverse iterator implementation
    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit> dynamic_array<t>::reverse_iterator<rit>::operator+(typename dynamic_array<t>::iterator<rit>::difference_type n) const {
        return iterator<rit>::operator-(n);
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit>& dynamic_array<t>::reverse_iterator<rit>::operator+=(typename dynamic_array<t>::iterator<rit>::difference_type n) {
        *this = iterator<rit>::operator-=(n);

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
    typename dynamic_array<t>::template iterator<rit> dynamic_array<t>::reverse_iterator<rit>::operator-(typename dynamic_array<t>::iterator<rit>::difference_type n) const {
        return iterator<rit>::operator+(n);
    }

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit>& dynamic_array<t>::reverse_iterator<rit>::operator-=(typename dynamic_array<t>::iterator<rit>::difference_type n) {
        *this = iterator<rit>::operator+=(n);

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

    template <typename t>
    template <typename rit>
    typename dynamic_array<t>::template iterator<rit>::difference_type dynamic_array<t>::reverse_iterator<rit>::operator-(const iterator<rit>& other) const {
        return this->index() - other.index();
    }

    // dynamic array implementation
    template <typename t>
    t* reallocate(t *list, size_t capacity) {
        auto new_list(new t[capacity]);

        for (int i(0); (i < capacity && &list[i] != nullptr); i++) {
            new_list[i] = list[i];
        }

        return new_list;
    }

    template <typename t>
    dynamic_array<t>::dynamic_array(std::initializer_list<t> list) :
    _capacity(list.size() > 0 ? list.size() * 2 : 10),
    _count(0),
    _list(new t[this->_capacity]) {
        for (auto const& value : list) {
            this->push_back(value);
        }
    }

    template <typename t>
    dynamic_array<t>::dynamic_array(size_t count, const t &value) :
    _capacity(count > 0 ? count * 2 : 10),
    _count(0),
    _list(new t[this->_capacity]) {
        for (int i(0); i < count; i++) {
            this->push_back(value);
        }
    }

    template <typename t>
    void dynamic_array<t>::push_back(t value) {
        this->resize(this->_count + 1, value);
    }

    template <typename t>
    void dynamic_array<t>::pop_back() {
        this->resize(this->_count - 1);
    }

    template <typename t>
    void dynamic_array<t>::insert(typename dynamic_array<t>::const_iterator_type iterator, t const& value) {
        this->resize(++this->_count, t());

        size_t index(std::distance(this->cbegin(), iterator));

        for (auto i(this->_count); i > index; i--) {
            this->_list[i] = this->_list[i - 1];
        }

        this->_list[index] = value;
    }

    template <typename t>
    void dynamic_array<t>::remove(typename dynamic_array<t>::const_iterator_type iterator) {
        size_t index(std::distance(this->cbegin(), iterator));

        for (auto i(index); i < this->_count; i++) {
            this->_list[i] = this->_list[i + 1];
        }

        this->resize(--this->_count);
    }

    template <typename t>
    void dynamic_array<t>::resize(size_t size, t const& value) {
        if (size == this->_capacity) {
            this->_capacity *= 2;
            this->_list = reallocate<t>(this->_list, this->_capacity);

        } else if (size <= this->_capacity / 4) {
            this->_capacity /= 2;
            this->_list = reallocate<t>(this->_list, this->_capacity);
        }

        if (size > this->_count) {
            for (int i(this->_count); i < size; i++) {
                this->_list[i] = value;
            }
        }

        this->_count = size;
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