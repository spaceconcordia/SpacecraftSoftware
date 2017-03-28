#include "priority_queue.h"

#include <stdbool.h>

bool is_lower_priority(struct task current, struct task other);

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
bool insert_task(struct priority_queue* p_q, struct task tsk){
  //compare the task w/ elements of the priority queue, swap

}
struct task top_task(const struct priority_queue* p_q) {
  return p_q->array[0];
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
