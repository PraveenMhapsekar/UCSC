#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define SLEEP 5

void* fn(void* argval){
    fprintf(stderr,"Sleeping '%d' .. \n",SLEEP);
    sleep(SLEEP);
    fprintf(stderr,"Inside fn with message \"%s\".\n",argval);

		pthread_exit((void*)6);
}

int main(){
    pthread_t tid;
    int st=0, retval;
    pthread_attr_t tattr;
    char* targ=(char*)malloc(sizeof(char)*10);

	  fprintf(stderr,"PID==%d\n",getpid());
    pthread_attr_init(&tattr);
    pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_JOINABLE);
    // pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);

    strcpy(targ,"abcd");
    pthread_create(&tid, &tattr, fn, (void*)targ);
		// system("ps -mL");

    retval = pthread_join(tid, (void **)&st);
		// system("ps -mL");

		sleep(3);
		// system("ps -mL");
    
		printf("Exiting with rc=%d... \n",st);
    return 0;
}
