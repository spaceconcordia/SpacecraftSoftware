#include <time.h>
#include "task.h"

struct task {
  int id;
  enum task_priority priority;
  time_t creation_time;
  enum task_type type;
};
