//
// Created by 임정운 on 2023/03/30.
//

#include <benchmark/benchmark.h>
#include <vector>
#include <singly_linked_list.h>

static void bm_std_resize_benchmark_001(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> list(5);

        list.resize(9);
    }
}

static void bm_std_resize_benchmark_002(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> list(4);

        list.resize(9);
    }
}

static void bm_resize_benchmark_001(benchmark::State& state) {
    for (auto _ : state) {
        tk::singly_linked_list<int> list(5);

        list.resize(9);
    }
}

static void bm_resize_benchmark_002(benchmark::State& state) {
    for (auto _ : state) {
        tk::singly_linked_list<int> list(4);

        list.resize(9);
    }
}

BENCHMARK(bm_std_resize_benchmark_001)->Name("benchmark_singly_linked_list/std_resize_001")->Iterations(10000);
BENCHMARK(bm_std_resize_benchmark_002)->Name("benchmark_singly_linked_list/std_resize_002")->Iterations(10000);
BENCHMARK(bm_resize_benchmark_001)->Name("benchmark_singly_linked_list/resize_001")->Iterations(10000);
BENCHMARK(bm_resize_benchmark_002)->Name("benchmark_singly_linked_list/resize_002")->Iterations(10000);
BENCHMARK_MAIN();