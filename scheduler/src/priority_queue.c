#include "priority_queue.h"

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

void kill_priority_queue(struct priority_queue* p_q) {
  free(p_q->array);
  p_q->array = NULL;
  p_q->capacity = 0;
  p_q->size = 0;
}
