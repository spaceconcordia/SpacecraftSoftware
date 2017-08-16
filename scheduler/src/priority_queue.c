#include "priority_queue.h"
#include <assert.h>
#include <stdbool.h>
#include <time.h>

bool is_lower_priority(struct task current, struct task other);
void max_heapify(struct priority_queue* p_q, size_t node_index);
int parent(size_t i);
bool decrease_creation_time(struct priority_queue* p_q, int task_id, time_t t);
void assertion_test(const struct priority_queue* p_q);

const time_t MAX_TIME = (time_t)((unsigned long long)(1LL << (8 * sizeof(time_t) - 1)) - 1);
time_t START_TIME;

struct priority_queue init_priority_queue(size_t capacity) {
    struct priority_queue p_q = { .capacity = capacity, .capacity_copy = capacity, .size = 0, .size_copy = 0 };
    p_q.array = malloc(sizeof(struct task) * capacity);
    p_q.array_copy = p_q.array;
    START_TIME = time(NULL);
    return p_q;
}

bool insert_task(struct priority_queue* p_q, struct task tsk) {
  assertion_test(p_q);
  assert(tsk.creation_time >= 0 && tsk.creation_time < (START_TIME + 3153600000)); //check that creation time isn't negative or 100 years from now.
  assert(tsk.priority >= LOW && tsk.priority <= HIGH);
  assert(tsk.type >= EMPTY && tsk.type <= GET_TIME);
  if (p_q->size != p_q->capacity) {
    p_q->size += 1;
    p_q->size_copy += 1;
    p_q->array[p_q->size - 1].id = tsk.id;
    p_q->array[p_q->size - 1].type = tsk.type;
    p_q->array[p_q->size - 1].priority = LOW;
    p_q->array[p_q->size - 1].creation_time = MAX_TIME;
    increase_priority(p_q, tsk.id, tsk.priority);
    decrease_creation_time(p_q, tsk.id, tsk.creation_time);
    return true;
  }
  else return false;
}

bool top_task(const struct priority_queue* p_q, struct task* t) {
  assertion_test(p_q);
  if (p_q->size != 0) {
    *t = p_q->array[0];
    return true;
  }
  else return false;
}

bool pop_task(struct priority_queue* p_q, struct task* t) {
  assertion_test(p_q);
  if (p_q->size != 0) {
    *t = p_q->array[0];
    return kill_task(p_q, p_q->array[0].id);
  }
  else return false;
}

bool increase_priority(struct priority_queue* p_q, int task_id, enum task_priority new_priority) {
  assertion_test(p_q);
  assert(new_priority >= LOW && new_priority <= HIGH);
  size_t i = 0;
  for (; i < p_q->size; i++) {
    if (p_q->array[i].id == task_id) {
        break;
    }
  }
  if (i == p_q->size) return false;

  if (new_priority > p_q->array[i].priority)
    p_q->array[i].priority = new_priority;
  else return false;

  while (i > 0 && is_lower_priority(p_q->array[parent(i)], p_q->array[i])) {
    struct task temp = p_q->array[parent(i)];
    p_q->array[parent(i)] = p_q->array[i];
    p_q->array[i] = temp;
    i = parent(i);
  }
  return true;
}

void clear_priority_queue(struct priority_queue* p_q) {
  assertion_test(p_q);
  p_q->size = 0;
  p_q->size_copy = 0;
}

bool kill_task(struct priority_queue* p_q, int task_id) {
  assertion_test(p_q);
  size_t i = 0;
  for (; i < p_q->size; i++) {
    if (p_q->array[i].id == task_id) {
        break;
    }
  }
  if (i == p_q->size) return false;

  p_q->array[i].priority = LOW;
  p_q->array[i].creation_time = MAX_TIME;
  max_heapify(p_q, i);
  p_q->size--;
  p_q->size_copy--;
  return true;
}

void kill_priority_queue(struct priority_queue* p_q) {
  free(p_q->array);
  p_q->array = NULL;
  p_q->size = 0;
  p_q->size_copy = 0;
}

bool is_lower_priority(struct task current, struct task other){
  if (current.priority == other.priority){
    return (current.creation_time < other.creation_time);
  } else {
    return (current.priority < other.priority);
  }
}

void max_heapify(struct priority_queue* p_q, size_t node_index) {
  assertion_test(p_q);
  size_t left = 2 * node_index + 1;
  size_t right = 2 * node_index + 2;
  size_t largest;

  if (left < p_q->size && !is_lower_priority(p_q->array[left], p_q->array[node_index])) {
    largest = left;
  }
  else largest = node_index;

  if (right < p_q->size && !is_lower_priority(p_q->array[right], p_q->array[node_index])) {
    largest = right;
  }

  if (largest != node_index) {
    struct task temp = p_q->array[node_index];
    p_q->array[node_index] = p_q->array[largest];
    p_q->array[largest] = temp;
    max_heapify(p_q, largest);
  }
}

int parent(size_t i) {
  assert(i != 0);
  return (i-1)/2;
}

bool decrease_creation_time(struct priority_queue* p_q, int task_id, time_t t) {
  assertion_test(p_q);
  assert(t >= 0 && t < (START_TIME + 3153600000));
  size_t i = 0;
  for (; i < p_q->size; i++) {
    if (p_q->array[i].id == task_id) {
        break;
    }
    return false;
  }

  if (t < p_q->array[i].creation_time)
    p_q->array[i].creation_time = t;
  else return false;

  while (i > 0 && is_lower_priority(p_q->array[parent(i)], p_q->array[i])) {
    struct task temp = p_q->array[parent(i)];
    p_q->array[parent(i)] = p_q->array[i];
    p_q->array[i] = temp;
    i = parent(i);
  }
  return true;
}

void assertion_test(const struct priority_queue* p_q) {
  assert(p_q->capacity == p_q->capacity_copy);
  assert(p_q->size == p_q->size_copy);
  assert(p_q->array == p_q->array_copy);
  assert(p_q->size <= p_q->capacity);
}
