//
// Created by 임정운 on 2023/03/30.
//

#include <benchmark/benchmark.h>
#include <forward_list>
#include <singly_linked_list.h>

static void bm_std_constructor_001(benchmark::State& state) {
    for (auto _ : state) {
        std::forward_list<int> list(1);
    }
}

static void bm_std_constructor_002(benchmark::State& state) {
    for (auto _ : state) {
        std::forward_list<int> list(10);
    }
}

static void bm_tk_constructor_001(benchmark::State& state) {
    for (auto _ : state) {
        tk::singly_linked_list<int> list(1);
    }
}

static void bm_tk_constructor_002(benchmark::State& state) {
    for (auto _ : state) {
        tk::singly_linked_list<int> list(10000);
    }
}

template <typename t>
class dummy {
private:
    struct node {
        t _value;
        node* _next;

        explicit node(t const& value = t()) :
        _value(value),
        _next(nullptr) {}
    };

private:
    node* _before_front;
    node* _back;
    size_t _count;

public:
    explicit dummy(size_t n, t const& value = t()) :
    _before_front(new node()),
    _back(nullptr),
    _count(0) {
        for (int i(0); i < n; i++) {
            if (this->_before_front->_next == nullptr) {
                this->_before_front->_next = std::move(new node(value));
                this->_back = this->_before_front->_next;

            } else {
                auto new_node(new node(value));
                new_node->_next = this->_before_front->_next;
                this->_before_front->_next = new_node;
            }

            this->_count++;
        }
    }
    ~dummy() {
        auto current(this->_before_front);

        while (current) {
            auto temp(current->_next);
            delete current;
            current = temp;
        }
    }
};

static void bm_dummy_constructor_001(benchmark::State& state) {
    for (auto _ : state) {
        dummy<int> list(1);
    }
}

static void bm_dummy_constructor_002(benchmark::State& state) {
    for (auto _ : state) {
        dummy<int> list(10);
    }
}

//BENCHMARK(bm_std_constructor_001)->Name("benchmark_singly_linked_list/std_constructor_001")->Iterations(100000);
BENCHMARK(bm_std_constructor_002)->Name("benchmark_singly_linked_list/std_constructor_002")->Iterations(10);
//BENCHMARK(bm_tk_constructor_001)->Name("benchmark_singly_linked_list/tk_constructor_001")->Iterations(100000);
//BENCHMARK(bm_tk_constructor_002)->Name("benchmark_singly_linked_list/tk_constructor_002")->Iterations(10);
//BENCHMARK(bm_dummy_constructor_001)->Name("benchmark_singly_linked_list/dummy_constructor_001")->Iterations(100000);
BENCHMARK(bm_dummy_constructor_002)->Name("benchmark_singly_linked_list/dummy_constructor_002")->Iterations(10);
BENCHMARK_MAIN();