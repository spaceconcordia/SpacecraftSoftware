#ifndef SCHEDULER_PRIORITY_QUEUE_H
#define SCHEDULER_PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include "task.h"

/*
 * A priority queue consists of the following members:
 *
 *   array: pointer to a dynamically-allocated array of tasks.
 *   capacity: max number of tasks that the priority queue can hold.
 *   size: number of tasks in the priority queue at a given moment.
 */
struct priority_queue;

/*
 * Creates and returns an empty priority queue with the given capacity. Note
 * that this function performs dynamic memory allocation, and therefore should
 * only be called on program startup as per the JPL coding guidelines.
 */
struct priority_queue init_priority_queue(size_t capacity);

/*
 * Inserts a task into the priority queue. Returns true if successful, false if
 * unsuccessful (for example, if the priority queue is full).
 */
bool insert_task(struct priority_queue* p_q, struct task tsk);

/*
 * Assigns the highest priority task of the priority queue to the task pointer.
 * Returns true if successful, false if unsuccessful (for example, if there are
 * no tasks in the priority queue).
 */
bool top_task(const struct priority_queue* p_q, struct task* t);

/*
 * Assigns the highest priority task of the priority queue to the task pointer
 * and removes the task. Returns true if successful, false if unsuccessful (for
 * example, if there are no tasks in the priority queue).
 */
bool pop_task(struct priority_queue* p_q, struct task* t);

/*
 * Increases the priority of the task with the specified task_id. Returns true
 * if successful, false if unsuccessful (for example, if the task does not
 * exist).
 */
bool increase_priority(struct priority_queue* p_q, int task_id, enum task_priority new_priority);

/*
 * Removes all tasks from the priority queue.
 */
void clear_priority_queue(struct priority_queue* p_q);

/*
 * Removes the task with the specified task_id from the queue. Returns treu if
 * successful, false if unsuccessful (for example, if the task does not exist).
 */
bool kill_task(struct priority_queue* p_q, int task_id);

/*
 * Deallocates memory for the priority queue.
 */
void kill_priority_queue(struct priority_queue* p_q);

#endif
