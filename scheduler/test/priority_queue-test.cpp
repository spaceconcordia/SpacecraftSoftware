#include "gtest/gtest.h"
extern "C" {
#include "priority_queue.h"
}

TEST(PriorityQueueTest, InsertTask) {
  struct task tsk = create_task(0, LOW, EMPTY);
  struct priority_queue p_q = init_priority_queue(10);
  EXPECT_EQ(insert_task(p_q, tsk), true);
  EXPECT_EQ(p_q.size, 1);
}
