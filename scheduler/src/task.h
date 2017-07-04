#ifndef SCHEDULER_TASK_H
#define SCHEDULER_TASK_H

enum task_type { EMPTY, PING, REBOOT, GET_TIME };
enum task_priority { LOW, MEDIUM, HIGH }
struct task;
struct task create_task(int id, enum task_priority priority, enum task_type type);

#endif
