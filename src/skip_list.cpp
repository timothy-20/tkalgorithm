//
// Created by 임정운 on 2023/03/31.
//

#include <skip_list.h>

namespace tk {
    template <typename t>
    uint32_t skip_list<t>::get_level() const {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_real_distribution<float> distributor(0.0, 1.0);
        uint32_t level(0);

        while (distributor(generator) < this->_percentage && level < this->_max_level) {
            level++;
        }

        return level;
    }

    template <typename t>
    bool skip_list<t>::is_contain(t const& value, std::vector<node*>& prev_nodes, skip_list<t>::node*& target_node) const {
        prev_nodes = std::vector<node*>(this->_max_level+1, nullptr);
        target_node = this->_head;

        for (int i(this->_current_level); i >= 0; i--) { // 현재의 최대 레벨(express lane)부터 0번 레벨(normal lane)까지 순회
            while (target_node->_next[i] && target_node->_next[i]->_value < value) { // 노드의 값보다 크거나 같은 값인 노드를 발견할 때까지 순회
                target_node = target_node->_next[i];
            }

            prev_nodes[i] = target_node; // 노드보다 크거나 nullptr 값 이전의 값을 해당하는 레벨에 저장
        }

        if (target_node->_next[0] && target_node->_next[0]->_value == value) {
            target_node = target_node->_next[0];

            return true;
        }

        return false;
    }

    template <typename t>
    bool skip_list<t>::is_contain(t const& value) const {
        std::vector<node*> prev_nodes;
        node* target_node;

        return this->is_contain(value, prev_nodes, target_node);
    }

    template <typename t>
    void skip_list<t>::insert(t const& value) {
        std::vector<node*> prev_nodes;
        node* temp_node; // normal lane에 있는 삽입할 값의 바로 전에 해당하는 값을 가지고 있는 노드

        if (this->is_contain(value, prev_nodes, temp_node)) {
            return;
        }

        uint32_t new_level(this->get_level());

        if (new_level > this->_current_level) {
            for (int i(this->_current_level+1); i <= new_level; i++) {
                prev_nodes[i] = temp_node; // 확장된 레벨만큼 이전 노드를 가르키도록 설정
            }

            this->_current_level = new_level;
        }

        temp_node = new node(this->_current_level, value);

        for (int i(0); i <= this->_current_level; i++) {
            temp_node->_next[i] = prev_nodes[i]->_next[i]; // 이전 노드가 가르키고 있는 다음 노드를 생성한 노드의 다음에 삽입
            prev_nodes[i]->_next[i] = temp_node; // 이전 노드가 다음 노드로 생성한 노드를 가르키도록 삽입
        }

        this->_count++;
    }

    template <typename t>
    void skip_list<t>::remove(t const& value) {
        std::vector<node*> prev_nodes;
        node* target_node; // 제거 대상 노드

        if (!this->is_contain(value, prev_nodes, target_node)) {
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

        this->_count--;
    }

    template class skip_list<int>;
}