//
// Created by 임정운 on 2023/04/05.
//

#include <gtest/gtest.h>
#include <xor_linked_list.h>

TEST(test_suite_xor_linked_list, initialize_test) {

}

TEST(test_suite_xor_linked_list, push_front_test) {
    tk::xor_linked_list<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    EXPECT_EQ(list.count(), 3);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);
}

TEST(test_suite_xor_linked_list, pop_front_test) {
    tk::xor_linked_list<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_front();
    list.pop_front();

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);

    list.pop_front();

    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.count(), 0);

    list.pop_front(); // 빈 list에 대한 pop 시도에 대한 테스트
}

TEST(test_suite_xor_linked_list, push_back_test) {
    tk::xor_linked_list<int> list;

    list.push_back(1);
    list.push_back(2);

    EXPECT_EQ(list.count(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

TEST(test_suite_xor_linked_list, pop_back_test) {
    tk::xor_linked_list<int> list;


}