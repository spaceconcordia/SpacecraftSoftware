#include "task.h"

struct task create_task(int id, enum task_priority priority, enum task_type type) {
  struct task t = { .id = id, .priority = priority, .creation_time = time(NULL), .type = type};
  return t;
}
