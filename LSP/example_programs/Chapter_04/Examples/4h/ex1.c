#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sched.h>

#define SLEEP 4

void* fn(void* argval){
    fprintf(stderr,"Sleeping '%d' .. \n",SLEEP);
    sleep(SLEEP);
    fprintf(stderr,"Inside fn with message \"%s\".\n",argval);

		pthread_detach(pthread_self());
}

int main(){
    pthread_t tid;
    int st, rc;
    pthread_attr_t tattr;
    char* targ=(char*)malloc(sizeof(char)*10);
		struct sched_param param[1];

/*
After these attributes have been set, a thread can be created with the specified attributes using pthread_create(). Using these routines does not affect the current running thread. 
*/
    pthread_attr_init(&tattr);
//  pthread_attr_setschedpolicy(&tattr, SCHED_OTHER); // default
		param->sched_priority=0;
    rc=pthread_attr_setschedparam(&tattr, param);
		fprintf(stderr,"RC => pthread_attr_setschedparam = %d.\n",rc);

    strcpy(targ,"abcd");
    rc=pthread_create(&tid, &tattr, fn, (void*)targ);
		fprintf(stderr,"RC => pthread_create = %d.\n",rc);

    printf("Exiting ... \n");

    rc = pthread_join(tid, (void **)&st);
		fprintf(stderr,"RC => pthread_join = %d.\n",rc);

		rc = pthread_attr_destroy(&tattr);
		fprintf(stderr,"RC => pthread_attr_destroy = %d.\n",rc);

    return 0;
}
