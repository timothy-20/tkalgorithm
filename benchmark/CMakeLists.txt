FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.7.1
)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
FetchContent_MakeAvailable(benchmark)

add_executable(
        benchmarks
        singly_linked_list_benchmark.cpp
)

target_compile_features(benchmarks PRIVATE cxx_std_20)
target_link_libraries(benchmarks PRIVATE library benchmark::benchmark)