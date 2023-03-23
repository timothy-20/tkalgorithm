//
// Created by jungu on 3/21/2023.
//

#include <iostream>

namespace tk {
    template <typename t>
    class dynamic_array {
    private:
        size_t _capacity;
        size_t _count;
        t* _list; // base-array에 iterator를 구성?

    private:
        static t* reallocate(t *list, size_t capacity);
        void grow_capacity();
        void shrink_capacity();

    public:
        explicit dynamic_array(size_t capacity) :
        _capacity(capacity > 0 ? capacity : 10),
        _count(0),
        _list(new t[this->_capacity]) {}
        ~dynamic_array() { delete[] this->_list; }
        void add(t value);
        void insert(t value, size_t index);
        void remove_last();
        void remove(size_t index);
        t& operator[] (size_t index); // throwable
        size_t count() const { return this->_count; }
        size_t capacity() const { return this->_capacity; }
    };
}