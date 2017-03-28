#include "priority_queue.h"

void max_heapify(struct priority_queue* p_q, size_t node_index);

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

bool top_task(const struct priority_queue* p_q, struct task* t) {
  if (p_q->size != 0) {
    *t = p_q->array[0];
    return true;
  }
  else
    return false;
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
