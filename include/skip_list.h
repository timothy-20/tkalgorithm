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
        float _percentage;
        node* _head;

    private:
        uint32_t get_level() const {
            std::random_device random_device;
            std::mt19937 generator(random_device());
            std::uniform_real_distribution<float> distributor(0.0, 1.0);
            uint32_t level(0);

            while (distributor(generator) < this->_percentage && level < this->_max_level) {
                level++;
            }

            return level;
        }

        std::vector<node*> search_prev(t const& value) const {
            auto prev_nodes(std::vector<node*>(this->_max_level+1, nullptr));
            auto cursor_node(this->_head);

            for (int i(this->_current_level); i >= 0; i--) {
                while (cursor_node->_next[i] && cursor_node->_next[i]->_value < value) {
                    cursor_node = cursor_node->_next[i];
                }

                prev_nodes[i] = cursor_node;
            }

            return prev_nodes;
        }

    public:
        explicit skip_list(size_t max_level, float percentage) :
        _max_level(max_level), // 최대 레벨 제한
        _percentage(percentage), // 높은 레벨이 나올 확률
        _current_level(0), // 현재 노드의 최대 레벨
        _head(new node(max_level)) {
            // ...
        }
        skip_list(std::initializer_list<t> list) {

        }
        skip_list(size_t max_level) : skip_list(max_level, 0.5) {}
        void insert(t const& value) {
            auto prev_nodes(std::vector<node*>(this->_max_level + 1, nullptr));
            auto temp_node(this->_head);

            for (int i(this->_current_level); i >= 0; i--) { // 현재의 최대 레벨(express lane)부터 0번 레벨(normal lane)까지 순회
                while (temp_node->_next[i] && temp_node->_next[i]->_value < value) { // 노드의 값보다 크거나 같은 값인 노드를 발견할 때까지 순회
                    temp_node = temp_node->_next[i];
                }

                prev_nodes[i] = temp_node->_next[i]; // 노드보다 크거나 nullptr 값 이전의 값을 해당하는 레벨에 저장
            }

            uint32_t new_level(this->get_level());

            if (new_level > this->_current_level) {
                for (int i(this->_current_level+1); i <= new_level; i++) {
                    prev_nodes[i] = temp_node; // 최소 값에 대한 노드로 확장된 공간 초기화
                }

                this->_current_level = new_level;
            }

            temp_node = new node(this->_current_level, value);

            for (int i(0); i <= this->_current_level; i++) {
                temp_node->_next[i] = prev_nodes[i]->_next[i]; // 이전 노드가 가르키고 있는 다음 노드를 생성한 노드의 다음에 삽입
                prev_nodes[i]->_next[i] = temp_node; // 이전 노드가 다음 노드로 생성한 노드를 가르키도록 삽입
            }
        }

        void remove(t const& value) {
            auto prev_nodes(this->search_prev(value));
            auto target_node(prev_nodes[0]->_next[0]);

            if (target_node->_value != value) {
                return;
            }

            for (int i(0); i <= this->_current_level; i++) {
                if (prev_nodes[i]->_next[i] == target_node) { // 이전 노드에서 가르키는 노드가 대상 노드인지 확인
                    prev_nodes[i]->_next[i] = target_node->_next[i]; // 대상 노드가 가르키고 있는 다음 노드를 덮어 씌우도록 대입
                }
            }

            while (this->_current_level > 0 && this->_head->_next[this->_current_level] == nullptr) { // 헤더의 최대 레벨부터 순회하면서 비어있는지 확인
                this->_current_level--;
            }
        }

        bool is_contain(t const& value) const {

            return true;
        }
    };

    template class skip_list<int>;
}