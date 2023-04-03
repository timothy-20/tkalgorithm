//
// Created by 임정운 on 2023/03/29.
//

#include <gtest/gtest.h>
#include <skip_list.h>

TEST(test_suite_skip_list, initializer_test) {

}

TEST(test_suite_skip_list, insert_test) {
    tk::skip_list<int> list(5, 0.5);

    list.insert(3);
    list.insert(6);
    list.insert(7);
    list.insert(9);
    list.insert(12);
}

TEST(test_suite_skip_list, remove_test) {

}

TEST(test_suite_skip_list, contain_test) {

}