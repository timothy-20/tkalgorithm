//
// Created by aircuve on 2023-03-23.
//

#include <gtest/gtest.h>
#include <singly_linked_list.h>

TEST(test_suite_singly_linked_list, initialize_test) {
    tk::singly_linked_list<int> list1{ 0, 1, 2 };
    tk::singly_linked_list<int> list2(3, 0);
    int count(0);

    EXPECT_EQ(list1.count(), 3);
    EXPECT_EQ(list2.count(), 3);

    for (auto const& value : list1) {
        EXPECT_EQ(value, count);

        count++;
    }

    for (auto const& value : list2) {
        EXPECT_EQ(value, 0);
    }
}

TEST(test_suite_singly_linked_list, push_front_test) {
    tk::singly_linked_list<int> list;

    for (int i(0); i < 3; i++) {
        list.push_front(i);
    }

    EXPECT_EQ(list.count(), 3);
    EXPECT_EQ(list.front(), 2);
}

TEST(test_suite_singly_linked_list, pop_front_test) {
    tk::singly_linked_list<int> list;

    for (int i(0); i < 3; i++) {
        list.push_front(i);
    }

    EXPECT_EQ(list.count(), 3);

    for (int i(2); i >= 0; i--) {
        EXPECT_EQ(list.front(), i);
        list.pop_front();
    }

    EXPECT_EQ(list.count(), 0);
}

TEST(test_suite_singly_linked_list, assign_test) {
    tk::singly_linked_list<int> list;

    for (int i(0); i < 5; i++) {
        list.push_front(0);
    }

    auto iterator1(list.begin());

    list.assign(iterator1, 10);
    list.assign(++iterator1, 2);
    list.assign(++iterator1, 3);

    auto iterator2(list.begin());

    EXPECT_EQ(*(iterator2++), 10);
    EXPECT_EQ(*(iterator2++), 2);
    EXPECT_EQ(*(iterator2++), 3);
    EXPECT_EQ(*iterator2, 0);
}

TEST(test_suite_singly_linked_list, insert_after_test) {
    tk::singly_linked_list<int> list;

    list.push_front(1);
    list.insert_after(list.cbegin(), 2);

    auto iterator(list.begin());

    for (int i(1); i < 3; i++) {
        EXPECT_EQ(*(iterator++), i);
    }
}

TEST(test_suite_singly_linked_list, remove_after_test) {
    tk::singly_linked_list<int> list{ 2, 1 };

    list.remove_after(list.cbegin());
    EXPECT_EQ(list.front(), 2);
}

TEST(test_suite_singly_linked_list, before_front_test) {
    tk::singly_linked_list<int> list{ 1, 2 };

    list.insert_after(list.before_begin(), 0);
    EXPECT_EQ(list.front(), 0);
}

// 기본적인 list의 크기 증가 및 감소에 대한 테스트
TEST(test_suite_singly_linked_list, resize_test) {
    tk::singly_linked_list<int> list{ 1, 2, 3 };

    list.resize(5);

    int count1(0);

    for (auto const& value : list) {
        count1++;

        if (count1 > 3) {
            EXPECT_EQ(value, 0);

        } else {
            EXPECT_EQ(value, count1);
        }
    }

    EXPECT_EQ(count1, 5);

    int count2(0);

    list.resize(2);

    for (auto const& value : list) {
        count2++;

        EXPECT_EQ(value, count2);
    }

    EXPECT_EQ(count2, 2);
}

TEST(test_suite_singly_linked_list, iterator_test_001) {
    tk::singly_linked_list<int> list;

    list.push_front(4);
    list.push_front(3);
    list.push_front(7);

    for (auto& element : list) {
        if (element == 3) {
            element = 6;
        }
    }

    EXPECT_EQ(*(++list.begin()), 6);
}

TEST(test_suite_singly_linked_list, iterator_test_002) {
    tk::singly_linked_list<int> list;

    list.push_front(2);
    list.push_front(8);
    list.push_front(6);

    auto iterator(list.begin());

    EXPECT_EQ(*(++iterator), 8);
    EXPECT_EQ(*(iterator++), 8);
    EXPECT_EQ(*iterator, 2);
    EXPECT_TRUE(++iterator == list.end());
}