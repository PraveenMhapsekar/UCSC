#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define SLEEP 5

void* fn(void* argval){
    fprintf(stderr,"Sleeping '%d' .. \n",SLEEP);
    // sleep(SLEEP);
    sleep(20);
    fprintf(stderr,"Inside fn with message \"%s\".\n",argval);

		pthread_detach(pthread_self());
}

int main(){
    pthread_t tid;
    int st, retval;
	  struct sched_param param;
    char* targ=(char*)malloc(sizeof(char)*10);

/*
		Processes scheduled under one of the real-time policies 
		(SCHED_FIFO, SCHED_RR) have a sched_priority value in the 
		range 1 (low) to 99 (high).  (As the numbers imply, real-time 
		processes always have higher priority than normal
		processes.)  Note well: POSIX.1-2001 only requires an 
		implementation to support a minimum 32 distinct priority levels 
		for the real-time policies, and some systems supply just this 
		minimum.  Portable programs should use sched_get_priority_min(2) 
		and sched_get_priority_max(2) to find the range of priorities 
		supported for a particular policy.
*/

	  param.sched_priority = 99;

		sleep(5);
	  // pthread_setschedparam(pthread_self(),SCHED_OTHER, &param);
	  pthread_setschedparam(pthread_self(),SCHED_FIFO, &param);

		sleep(5);
    strcpy(targ,"abcd");
    pthread_create(&tid, 0, fn, (void*)targ);

    retval = pthread_join(tid, (void **)&st);

    printf("Exiting ... \n");
    return 0;
}
