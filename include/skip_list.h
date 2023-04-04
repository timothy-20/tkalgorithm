//
// Created by 임정운 on 2023/03/29.
//

#pragma once
#include <iostream>
#include <random>

namespace tk {
    template <typename t>
    class skip_list {
    private:
        struct node {
            std::vector<node*> _next;
            t _value;

            explicit node(size_t level, t const& value) :
            _next(std::vector<node*>(level+1, nullptr)),
            _value(value) {}
            node(size_t level) : node(level, t()) {}
            node() : node(0) {}
        };

    private:
        size_t _max_level;
        size_t _current_level;
        size_t _count;
        float _percentage;
        node* _head;

    private:
        uint32_t get_level() const;
        bool is_contain(t const& value, std::vector<node*>& prev_nodes, node*& target_node) const;

    public:
        explicit skip_list(size_t max_level, float percentage) :
        _max_level(max_level), // 최대 레벨 제한
        _percentage(percentage), // 높은 레벨이 나올 확률
        _count(0), // 노드의 갯수
        _current_level(0), // 현재 노드의 최대 레벨
        _head(new node(max_level)) {}
        skip_list(size_t max_level) : skip_list(max_level, 0.5) {}
        bool is_contain(t const& value) const;
        void insert(t const& value);
        void remove(t const& value);
        size_t count() const { return this->_count; }
    };
}