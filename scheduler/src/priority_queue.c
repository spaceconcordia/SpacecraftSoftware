#include "priority_queue.h"

struct priority_queue {
  struct task* array;
  size_t capacity; //const?
  size_t size;
};
