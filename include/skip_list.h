//
// Created by 임정운 on 2023/03/29.
//

#pragma once
#include <iostream>
#include <memory>
#include <dynamic_array.h>

namespace tk {
    template <typename kt, typename vt>
    class skip_list {
    private:
        struct node {
            kt _key;
            vt _value;
            dynamic_array<std::shared_ptr<node>> _forward;

            explicit node(kt key, vt value, size_t level) :
            _key(key),
            _value(value),
            _forward(level, nullptr) {}
        };

    private:

    public:

    };
}