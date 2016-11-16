// demo collision using global variable .. pthread_mutex_timedlock

#define NUMTHREADS 5
#define ITERS 3
#define TRIES 2

#define THREAD "Thread #"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// #include <linux/time.h>

void *fn();
int  counter = 0;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	int i=0;
	char *str[NUMTHREADS];
  int retval[NUMTHREADS];

	
  pthread_t t[NUMTHREADS];

	while	(i<NUMTHREADS) {
	 str[i]=malloc(50); 
	 sprintf(str[i],"%s%d",THREAD,i);
   if( (retval[i]=pthread_create( &t[i], NULL, &fn, str[i])) ) 
      printf("Thread creation failed: %d\n", retval[i]);

	 i+=1;
	}
	
	i=0;
	while	(i<NUMTHREADS) {
   pthread_join(t[i],NULL);
	 free(str[i]);

	 i+=1;
	}

	// destroys a mutex object, freeing the resources it might hold.
	pthread_mutex_destroy(&m1); // needed in certain implementations

  exit(0);
}

void *fn(void *str)
{
	int i=0;
	int rc=0;

	struct timespec ts[1];

	ts->tv_sec=1;
	ts->tv_nsec=0;

  printf("%s:Inside fn(): Thread '%d' Counter value: %d.\n",
			str, pthread_self(),counter);

	while (i++<ITERS) {
		
		sleep(1);
		
		rc=pthread_mutex_timedlock(&m1,ts);

   	counter++;
	 	sleep(i);			// sleep some arbitrary time to induce collisions
		
	  if (!rc)
   		pthread_mutex_unlock(&m1);
	}

  printf("%s: .. done with fn().\n",str);
	return 0;
}
