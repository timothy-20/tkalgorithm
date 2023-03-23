//
// Created by jungu on 3/21/2023.
//

#include <iostream>

namespace tk {
    template <typename t>
    class dynamic_array {
    private:
        t* _list; // base-array에 iterator를 구성
        uint32_t _capacity;
        uint32_t _count;

    private:
        void grow_capacity();
        void shrink_capacity();

    public:
        explicit dynamic_array(uint32_t capacity) :
        _list(new t[capacity]),
        _capacity(capacity),
        _count(0) {}
        ~dynamic_array() { delete[] this->_list; }
        void add(t value);
        void insert(t value, uint32_t index);
        void remove_last_object();
        void remove(t value, uint32_t index);
    };
}