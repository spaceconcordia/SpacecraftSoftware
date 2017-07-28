#ifndef SCHEDULER_TASK_RUNNER_H
#define SCHEDULER_TASK_RUNNER_H

#include <stdbool.h>
#include <stdlib.h>
#include "task.h"

//based on the type of the task, decides what action to take
// bool delegate_task(struct task* task, enum task_type type);

//reboots the system
void reboot();

//gets current time from the system
void get_time();

//sends out a ping
void ping();



#endif
