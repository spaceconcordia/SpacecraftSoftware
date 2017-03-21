#ifndef SCHEDULER_PRIORITY_QUEUE_H
#define SCHEDULER_PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include "task.h"

struct priority_queue;

struct priority_queue init_priority_queue(size_t capacity);

bool insert_task(struct priority_queue* p_q, struct task tsk);

struct task top_task(const struct priority_queue* p_q);

struct task pop_task(struct priority_queue* p_q);

bool increase_priority(struct priority_queue* p_q, struct task* t_p, enum task_priority new_priority);

void clear_priority_queue(struct priority_queue* p_q);

bool kill_task(struct priority_queue* p_q, struct task* t_p);

void kill_priority_queue(struct priority_queue* p_q);

#endif
