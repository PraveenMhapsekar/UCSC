#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define SLEEP 2

void* fn(void* argval){
	  int rc=7;
    fprintf(stderr,"Sleeping '%d' .. \n",SLEEP);
    sleep(SLEEP);
    fprintf(stderr,"Inside fn with message \"%s\".\n",argval);

		pthread_detach(pthread_self());
 		// pthread_exit((void*)rc);
	  // return (int *) rc;
}

int main(){
    pthread_t tid;
    int st=0, retval;
    pthread_attr_t tattr;
    char* targ=(char*)malloc(sizeof(char)*10);

	  fprintf(stderr,"PID==%d\n", getpid());
    pthread_attr_init(&tattr);
    // pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);

		// system("ps -mL");

    strcpy(targ,"abcd");
    // pthread_create(&tid, NULL, fn, (void*)targ);
    pthread_create(&tid, &tattr, fn, (void*)targ);

		sleep(2);
		// system("ps -mL");
    retval = pthread_join(tid, (void **)&st);

    printf("Exiting with rc=%d... \n",st);
		sleep(2);
		// system("ps -mL");
    return 0;
}
