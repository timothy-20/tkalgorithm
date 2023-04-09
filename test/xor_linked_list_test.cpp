//
// Created by 임정운 on 2023/04/05.
//

#include <gtest/gtest.h>
#include <xor_linked_list.h>

TEST(test_suite_xor_linked_list, initialize_test) {
    tk::xor_linked_list<int> list1{ 1, 2, 3, 4 };

    for (int i(1); i <= 4; i++) {
        EXPECT_EQ(list1[i-1], i);
    }

    tk::xor_linked_list<int> list2(4, 10);

    for (int i(0); i < 4; i++) {
        EXPECT_EQ(list2[i], 10);
    }

    tk::xor_linked_list<int> list3(4);

    for (int i(0); i < 4; i++) {
        EXPECT_EQ(list3[i], 0);
    }
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
    EXPECT_NO_THROW(list.pop_front()); // 빈 list에 대한 pop 시도에 대한 테스트
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

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_back();

    EXPECT_EQ(list.count(), 2);
    EXPECT_EQ(list.back(), 2);

    list.pop_back();

    EXPECT_TRUE(list.front() == list.back());

    list.pop_back();

    EXPECT_NO_THROW(list.pop_back()); // 빈 list에 대한 pop 시도에 대한 테스트
}

TEST(test_suite_xor_linked_list, access_test) {
    tk::xor_linked_list<int> list1{ 0, 1, 2 };

    for (int i(0); i < 3; i++) {
        EXPECT_EQ(list1[i], i);
    }

    tk::xor_linked_list<int> list2{ 1, 4, 2, 5 };

    EXPECT_EQ(list2[2], 2);

    tk::xor_linked_list<int> list3;

    EXPECT_ANY_THROW(list3[1]);
}