// demo collision using global variable .. pthread_mutex_lock()

/*

The following mutex types are supported:
PTHREAD_MUTEX_TIMED_NP - for ‘‘fast’’ mutexes.
PTHREAD_MUTEX_RECURSIVE_NP - for ‘‘recursive’’ mutexes.
PTHREAD_MUTEX_ERRORCHECK_NP - for ‘‘error checking’’ mutexes.

If the mutex is of the “normal” or "timed" type, the calling thread is suspended until the mutex is unlocked, thus effectively causing the calling thread to deadlock. 

If the mutex is of the ‘‘error checking’’ type, pthread_mutex_lock returns immediately with the error code EDEADLK. 

If the mutex is of the ‘‘recursive’’ type, pthread_mutex_lock succeeds and returns immediately, recording the number of times the calling thread has locked the mutex.

NP suffix indicates Non-Portable Extension to POSIX
*/

#define NUMTHREADS 5
#define ITERS 3
#define TRIES 2

#define THREAD "Thread #"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *fn();
int  counter = 0;

pthread_mutex_t m1;
pthread_mutexattr_t mutex_attr;

int main()
{
	int i=0,c=0;
	char *str[NUMTHREADS];
  int retval[NUMTHREADS];
	
  pthread_t t[NUMTHREADS];

	pthread_mutexattr_init(&mutex_attr);

	// NP suffix indicates Non-Portable Extension to POSIX
	pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_TIMED_NP);

	pthread_mutex_init(&m1,&mutex_attr);

	while	(i<NUMTHREADS) {
	 str[i]=malloc(50); 
	 sprintf(str[i],"%s%d",THREAD,i);
   if( (retval[i]=pthread_create( &t[i], NULL, &fn, str[i])) ) 
      printf("Thread creation failed: %d\n", retval[i]);

	 i+=1;
	}

	fprintf(stderr,"Enter a char:(PID==%d)\n:",getpid());
	c=getchar();
	
	i=0;
	while	(i<NUMTHREADS) {
   pthread_join(t[i],NULL);
	 free(str[i]);

	 i+=1;
	}

  // needed in some implementations
  pthread_mutexattr_destroy(&mutex_attr); 

	// destroys a mutex object, freeing the resources it might hold.
	pthread_mutex_destroy(&m1); // needed in some implementations

  exit(0);
}

void *fn(void *str)
{
	int i=0;

  printf("%s:Inside fn(): Thread '%d' Counter value: %d.\n",
			str, pthread_self(),counter);

	while (i++<ITERS) {
		
		sleep(i*i);
		
   	printf("%s:'%d' Trying to Acquire Mutex:Thread '%d':Counter value: %d.\n",
			str,i,pthread_self(),counter);

   	pthread_mutex_lock(&m1);
   	counter++;
  	printf("%s: .. Acquired lock in fn().\n",str);
	 	 sleep((i*i+1)/(i+1));			// sleep some arbitrary time to induce collisions
   	pthread_mutex_unlock(&m1);
  	printf("%s: .. Released lock in fn().\n",str);
	}

  printf("%s: .. done with fn().\n",str);
	return 0;
}
