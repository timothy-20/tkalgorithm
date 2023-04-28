//
// Created by aircuve on 2023-04-28.
//

#pragma once
#include <iostream>
#include <random>

namespace tk {
    template <typename T, size_t N>
    class sort_method {
    public:
        virtual static void sort_recursive(T (&values)[N]) = 0;
        virtual static void sort_iterative(T (&values)[N]) = 0;
    };

    template <typename T, size_t N>
    class quick_sort : public sort_method<T, N> {
    public:
        static void sort_recursive(T (&values)[N]) override {

        }

        static void sort_iterative(T (&values)[N]) override {

        }

    private:
        enum pivot_determine_type {
            FIRST,
            MIDDLE,
            LAST,
            RANDOM,
            AVERAGE
        };

    private:
        //void partition(T (&values)[N])

        static size_t determine_pivot_index(pivot_determine_type type, T (&values)[N]) {
            size_t pivot_index(0);

            switch (type) {
                case FIRST: return 0;
                case MIDDLE: return N / 2;
                case LAST: return N;
                case RANDOM: return get_random_index(N);
                case AVERAGE: return get_midian_of_midian_index(values);
            }

            return pivot_index;
        }

        static size_t get_random_index(size_t size) {
            std::random_device random_device;
            std::mt19937 generator(random_device());
            std::uniform_int_distribution<> distributor(0, size);

            return distributor(generator);
        }

        static size_t get_midian_of_midian_index(T (&values)[N]) {
            T first_value(values[0]);
            T middle_value(values[N / 2]);
            T last_value(values[N]);

            // 첫 번째 값이 3개의 값 중 중간 수준의 크기를 가진 경우
            if ((first_value < middle_value && first_value > last_value)
                || (first_value > middle_value && first_value < last_value)) {
                return first_value;
            }

            // 중간 값이 3개의 값 중 중간 수준의 크기를 가진 경우
            if ((first_value > middle_value && middle_value > last_value)
                && (last_value > middle_value && middle_value > first_value)) {
                return middle_value;
            }

            return last_value;
        }
    };

    template <typename t>
    class sorting_machine {
    public:
        template <int LENGTH>
        explicit sorting_machine(sort_method const& method, t (&values)[LENGTH]) :
                _method(method),
                _values(value),
                _length(LENGTH) {

        }

    private:
        sort_method _method;
        t (&_values)[];
        int _length;
    };
}