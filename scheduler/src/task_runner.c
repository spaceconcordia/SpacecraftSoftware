#include "task_runner.h"
#include <time.h>
#include <stdio.h>


bool delegate_task(struct task* task, enum task_type){
	switch (task.task_type){
		case REBOOT
			reboot();
			return true;
		case GET_TIME
			get_time();
			return true;
		case PING
			ping();
			return true;
		default :
			return false;
	}
}

void reboot(){
	//<------take some kind of safety precautions?----->
	
	
	//don't think this will work...
	//system(shutdown -r now);
	
}

void get_time(){
	//get the time, according to the internet
	time_t = time(NULL);
	struct tm *tm = localtime(&t);
	
	//save the time to a variable
	char time_got[] = asctime(tm);
	
	//now what do  ido with it?
	
}

void ping(){
	//Not quite sure what to do here
	printf("%s\n Ping!");
	
}