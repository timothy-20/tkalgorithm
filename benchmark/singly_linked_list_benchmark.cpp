//
// Created by 임정운 on 2023/03/30.
//

#include <benchmark/benchmark.h>
#include <singly_linked_list.h>

// list의 크기 증가 시, list의 count 및 대비 증가 크기를 비교하여 최적화된 resize 동작을 수행하는지에 대한 벤치마크
static void bm_resize_benchmark_001(benchmark::State& state) {
    tk::singly_linked_list<int> list(5);

    for (auto _ : state) {
        for (int i(0); i < state.range(0); i++) {
            list.resize(9);
            list.resize(5);
        }
    }
}

static void bm_resize_benchmark_002(benchmark::State& state) {
    tk::singly_linked_list<int> list(4);

    for (auto _ : state) {
        for (int i(0); i < state.range(0); i++) {
            list.resize(9);
            list.resize(5);
        }
    }
}

BENCHMARK(bm_resize_benchmark_001)->Name("benchmark_singly_linked_list/resize_001");
BENCHMARK(bm_resize_benchmark_002)->Name("benchmark_singly_linked_list/resize_002");
BENCHMARK(bm_resize_benchmark_001)->RangeMultiplier(2)->Range(50, 100);
BENCHMARK(bm_resize_benchmark_002)->RangeMultiplier(2)->Range(50, 100);
BENCHMARK_MAIN();