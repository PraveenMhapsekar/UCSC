// using pthread_exit()

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* 
 * http://docs.oracle.com/cd/E19963-01/html/821-1601/tlib-1.html#tlib-12602
 * Finishing Up
 * A thread can terminate its execution in the following ways:
 * -   By returning from its first (outermost) procedure, 
 *     the threads start routine.  (see ex1.c)
 * -   By calling pthread_exit(), supplying an exit rc. (see ex2.c)
 * -   By termination with POSIX cancel functions. See pthread_cancel().  
 *     (see ex3.c)
 *     The default behavior of a thread is to linger until some other thread has acknowledged its demise by “joining” with the lingering thread. This behavior is the same as the default pthread_create() attribute that is nondetached, see pthread_detach. The result of the join is that the joining thread picks up the exit rc of the terminated thread and the terminated thread vanishes.
 *
 *     An important special case arises when the initial thread, calling main(), returns from calling main() or calls exit(). This action causes the entire process to be terminated, along with all its threads. So, take care to ensure that the initial thread does not return from main() prematurely.
 *
 *     Note that when the main thread merely calls pthread_exit, the main thread terminates itself only. The other threads in the process, as well as the process, continue to exist. The process terminates when all threads terminate.
 *
 */

void *myfn( void *fnptr );

int	st=10;
pthread_t t3;

main()
{
     pthread_t t1, t2;
     char *s1 = "Thread 1";
     char *s2 = "Thread 2";
     char *s3 = "Thread 3";
     int  r1, r2, r3;
     int  r1j, r2j, r3j;
		 void *rc;

     r1 = pthread_create( &t1, NULL, myfn, (void*)s1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)s2);
     r3 = pthread_create( &t3, NULL, myfn, (void*)s3);

     r1j=pthread_join( t1, NULL);
     r2j=pthread_join( t2, NULL);

     // int pthread_join(pthread_t thread, void **retval);
     r3j=pthread_join( t3, &rc);

     printf("In main: Thread 1 returns: %d,%d\n",r1,r1j);
     printf("In main: Thread 2 returns: %d,%d\n",r2,r2j);
     printf("In main: Thread 3 returns: %d,%d,%d\n",r3,r3j,(int) rc);
     exit(0);

}

void *myfn( void *fnptr )
{
   pthread_t tid=pthread_self();
	 char *msg = (char *) fnptr;
	 int i=0;
	
	 while(i++<=12) {
	 	fprintf(stderr,"In %s: TID=%u and PID=%u\n",msg, tid,getpid());
		sleep(1);

		// pthread_equal returns 1 for match, else 0
	 	if (pthread_equal(tid,t3)) {
			sleep(2);		
	 		printf("Bailing out in t3 after 2 secs.\n\n");
			// exit(0);
			return (void *)7;
		}
	 }
	return (void *)6;
}	
