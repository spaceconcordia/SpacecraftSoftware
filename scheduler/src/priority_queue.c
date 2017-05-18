#include "priority_queue.h"
#include <stdbool.h>

bool is_lower_priority(struct task current, struct task other);
void max_heapify(struct priority_queue* p_q, size_t node_index);

const int MAX_TIME = 1 << (8 * sizeof(time_t) - 1) - 1;

struct priority_queue {
  struct task* array;
  size_t capacity; //const?
  size_t size;
};

struct priority_queue init_priority_queue(size_t capacity) {
    struct priority_queue p_q;
    p_q.array = malloc(sizeof(struct task) * capacity);
    p_q.capacity = capacity;
    p_q.size = 0;
    return p_q;
}

bool insert_task(struct priority_queue* p_q, struct task tsk) {
  if (p_q->size != p_q->capacity) {
    p_q->size += 1;
    p_q->array[p_q->size - 1].task_priority = LOW;
    p_q->array[p_q->size - 1].creation_time = MAX_TIME;
    increase_priority(p_q, p_q->task_id, p_q->task_priority);
    return true;
  }
  else return false;
}

bool top_task(const struct priority_queue* p_q, struct task* t) {
  if (p_q->size != 0) {
    *t = p_q->array[0];
    return true;
  }
  else return false;
}

bool increase_priority(struct priority_queue* p_q, int task_id, enum task_priority new_priority) {
  size_t i = 0;
  for (; i < p_q->size; i++) {
    if (p_q->array[i].id == task_id) {
        break;
    }
    return false;
  }

  if (new_priority > p_q->array[i].task_priority)
    p_q->array[i].task_priority = new_priority;
  else return false;

  while (i > 0 && p_q->array[parent(i)] < p_q->array[i]) {
    struct task temp = p_q->array[parent(i)];
    p_q->array[parent(i)] = p_q->array[i];
    p_q->array[i] = temp;
    i = parent(i);
  }
  return true;
}

void clear_priority_queue(struct priority_queue* p_q) {
  p_q->size = 0;
}

void kill_priority_queue(struct priority_queue* p_q) {
  free(p_q->array);
  p_q->array = NULL;
  p_q->capacity = 0;
  p_q->size = 0;
}

bool is_lower_priority(struct task current, struct task other){
  if (current.priority == other.priority){
    return (current.creation_time < other.creation_time);
  } else {
    return (current.priority < other.priority);
  }
}

void max_heapify(struct priority_queue* p_q, size_t node_index) {
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
  return (i-1)/2;
}
