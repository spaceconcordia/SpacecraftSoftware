#include <time.h>
#include "task.h"

struct task {
  int id;
  enum task_priority priority;
  time_t creation_time;
  enum task_type type;
};

struct task create_task(int id, enum task_priority priority, enum task_type type) {
  struct task t = { .id = id, .priority = priority, .creation_time = (unsigned) time(NULL), .type = type};
  return t;
}
