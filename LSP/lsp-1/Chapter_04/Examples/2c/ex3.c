// using pthread_cancel()

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* 
 * Finishing Up
 * A thread can terminate its execution in the following ways:
 * -   By returning from its first (outermost) procedure, 
 *     the threads start routine.  (see ex1.c)
 * -   By calling pthread_exit(), supplying an exit status. (see ex2.c)
 * -   By termination with POSIX cancel functions. See pthread_cancel().  
 *     (see ex3.c)
 *
 */

void *myfn( void *fnptr );

pthread_t t3;

main()
{
     pthread_t t1, t2;
     char *s1 = "Thread 1";
     char *s2 = "Thread 2";
     char *s3 = "Thread 3";
     int  r1, r2, r3;
     int  r1j, r2j, r3j;
		 void *status, *status2;

     r1 = pthread_create( &t1, NULL, myfn, (void*)s1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)s2);
     r3 = pthread_create( &t3, NULL, myfn, (void*)s3);

     r1j=pthread_join( t1, NULL);
     r2j=pthread_join( t2, &status2);
     r3j=pthread_join( t3, &status);

     printf("In main: Thread 1 returns: %d,%d\n",r1,r1j);
     printf("In main: Thread 2 returns: %d,%d,%d\n",r2,r2j,(int) status2);
     printf("In main: Thread 3 returns: %d,%d,%d\n",r3,r3j,(int) status);
     exit(0);

}

void *myfn( void *fnptr )
{
   pthread_t tid=pthread_self();
	 char *msg = (char *) fnptr;
	 int i=0;
   int st=10;
	
	 while(i++<=15) {
	 	fprintf(stderr,"In %s: TID=%u and PID=%u\n",msg, tid,getpid());
		sleep(1);

		// pthread_equal returns 1 for match, else 0
	 	if (pthread_equal(tid,t3)) {
	 		printf("Bailing out in t3 after 2 secs.\n");
			sleep(2);		
			// exit(0);
			return ((void *)st);
		}
	 }
}	
