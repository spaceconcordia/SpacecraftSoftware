#ifndef SCHEDULER_TASK_H
#define SCHEDULER_TASK_H

#include <time.h>

enum task_type { EMPTY, PING, REBOOT, GET_TIME };
enum task_priority { LOW, MEDIUM, HIGH };

struct task {
  int id;
  enum task_priority priority;
  time_t creation_time;
  enum task_type type;
};
struct task create_task(int id, enum task_priority priority, enum task_type type);

#endif
