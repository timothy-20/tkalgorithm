//
// Created by aircuve on 2023-03-20.
//

#include <gtest/gtest.h>
#include <queue.h>

TEST(TestSuite001, HandleQueueTest001) {
    tk::queue<int> new_queue;
    const int loop_count(3);

    for (int i(1); i <= loop_count; i++) {
        new_queue.enqueue(i);
    }

    for (int j(1); j <= loop_count; j++) {
        EXPECT_EQ(new_queue.dequeue(), j);
    }
}

TEST(TestSuite001, HandleQueueTest002) {

}