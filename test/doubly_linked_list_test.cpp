//
// Created by aircuve on 2023-03-27.
//

#include <gtest/gtest.h>
#include <doubly_linked_list.h>

TEST(test_suite_doubly_linked_list, initialize_test) {
    tk::doubly_linked_list<int> list1{ 1, 2, 3 };
    tk::doubly_linked_list<int> list2(3, 1);
    int count(1);

    EXPECT_EQ(list1.count(), 3);
    EXPECT_EQ(list2.count(), 3);

    for (auto const& value : list1) {
        EXPECT_EQ(value, count);
        count++;
    }

    for (auto const& value : list2) {
        EXPECT_EQ(value, 1);
    }
}

TEST(test_suite_doubly_linked_list, push_front_test) {
    tk::doubly_linked_list<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_EQ(list.count(), 3);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);
}

TEST(test_suite_doubly_linked_list, pop_front_test) {
    tk::doubly_linked_list<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    list.pop_front();
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.count(), 1);
    list.pop_front();
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.count(), 0);
}

TEST(test_suite_doubly_linked_list, push_back_test) {
    tk::doubly_linked_list<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.count(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(test_suite_doubly_linked_list, pop_back_test) {
    tk::doubly_linked_list<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    list.pop_back();
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.count(), 1);
    list.pop_back();
    EXPECT_EQ(list.back(), 0);
    EXPECT_EQ(list.count(), 0);
}

TEST(test_suite_doubly_linked_list, insert_test) {
    tk::doubly_linked_list<int> list;

    list.push_front(1);
    list.push_back(3);
    list.insert(list.cbegin() + 1, 2);
    EXPECT_EQ(list.count(), 3);

    int count(1);

    for (auto const& element : list) {
        EXPECT_EQ(element, count);

        count++;
    }
}

TEST(test_suite_doubly_linked_list, remove_test) {
    tk::doubly_linked_list<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.remove(list.cbegin() + 1);
    EXPECT_EQ(list.count(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(test_suite_doubly_linked_list, iterator_test) {
    tk::doubly_linked_list<int> list{ 0, 1, 2 };
    int count(0);

    for (auto const& value : list) {
        EXPECT_EQ(value, count);

        count++;
    }
}

TEST(test_suite_doubly_linked_list, reverse_iterator_test) {
    tk::doubly_linked_list<int> list { 2, 1, 0 };
    int count(0);

    for (auto iterator(list.crbegin()); iterator != list.crend(); iterator++) {
        EXPECT_EQ(*iterator, count);

        count++;
    }
}