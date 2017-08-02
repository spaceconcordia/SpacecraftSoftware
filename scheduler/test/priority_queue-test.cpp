#include "gtest/gtest.h"
extern "C" {
#include "priority_queue.h"
}

bool compare_tasks(struct task* t1, struct task* t2) {
  return (t1->id == t2->id) && (t1->priority == t2->priority) && (t1->creation_time == t2->creation_time) && (t1->type == t2->type);
}

TEST(PriorityQueueTest, InsertTask) {
  struct task tsk = create_task(0, LOW, EMPTY);
  struct priority_queue p_q = init_priority_queue(10);
  EXPECT_EQ(insert_task(&p_q, tsk), true);
  EXPECT_EQ(p_q.size, 1);
}

TEST(PriorityQueueTest, TopTask) {
  struct task tsk = create_task(0, LOW, EMPTY);
  struct task temp;
  struct priority_queue p_q = init_priority_queue(10);
  insert_task(&p_q, tsk);
  EXPECT_EQ(top_task(&p_q, &temp), true);
  EXPECT_EQ(compare_tasks(&tsk, &temp), true);
  EXPECT_EQ(p_q.size, 1);
}

TEST(PriorityQueueTest, PopTask) {
  struct task tsk = create_task(0, LOW, EMPTY);
  struct task temp;
  struct priority_queue p_q = init_priority_queue(10);
  insert_task(&p_q, tsk);
  EXPECT_EQ(p_q.size, 1);
  EXPECT_EQ(pop_task(&p_q, &temp), true);
  EXPECT_EQ(compare_tasks(&tsk, &temp), true);
  EXPECT_EQ(p_q.size, 0);
}

TEST(PriorityQueueTest, IncreasePriority) {
  struct task tsk = create_task(0, LOW, EMPTY);
  struct priority_queue p_q = init_priority_queue(10);
  insert_task(&p_q, tsk);
  EXPECT_EQ(increase_priority(&p_q, 0, MEDIUM), true);
  EXPECT_EQ(p_q.size, 1);
}

TEST(PriorityQueueTest, ClearPriorityQueue) {
  struct task tsk = create_task(0, LOW, EMPTY);
  struct priority_queue p_q = init_priority_queue(10);
  insert_task(&p_q, tsk);
  EXPECT_EQ(p_q.size, 1);
  clear_priority_queue(&p_q);
  EXPECT_EQ(p_q.size, 0);
}

TEST(PriorityQueueTest, KillTask) {
  struct task tsk1 = create_task(0, LOW, EMPTY);
  struct task tsk2 = create_task(1, LOW, EMPTY);
  struct priority_queue p_q = init_priority_queue(10);
  insert_task(&p_q, tsk1);
  insert_task(&p_q, tsk2);
  EXPECT_EQ(p_q.size, 2);
  EXPECT_EQ(kill_task(&p_q, 1), true);
  EXPECT_EQ(p_q.size, 1);
}
