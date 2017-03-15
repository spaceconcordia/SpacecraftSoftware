#include <time.h>
#include "task.h"

struct task {
  int id;
  int priority;
  time_t creation_time;
  enum TASK_TYPE task_type;
};
