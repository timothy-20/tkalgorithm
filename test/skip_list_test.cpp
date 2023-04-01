//
// Created by 임정운 on 2023/03/29.
//

#include <gtest/gtest.h>
#include <skip_list.h>

TEST(test_suite_skip_list, initializer_test) {
    EXPECT_NO_THROW(tk::skip_list<int> list);
}

TEST(test_suite_skip_list, insert_test) {
}