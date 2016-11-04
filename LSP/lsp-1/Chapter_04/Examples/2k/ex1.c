#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define NUMBER 16

void *myfn( void *fnptr );

main()
{
     pthread_t t1, t2, t3;
     int i1[] = {1,NUMBER/2};
     int i2[] = {(NUMBER/2)+1,NUMBER};
     int i3[] = {1,NUMBER};
     int  r1, r2, r3;

		 int status;

		 // sleep(2);

     r1 = pthread_create( &t1, NULL, myfn, (void*)i2);
     r2 = pthread_create( &t2, NULL, myfn, (void*)i1);
     r3 = pthread_create( &t3, NULL, myfn, (void*)i3);

		 // sleep(1);

/*
 * from man page
 *
 * The pthread_kill() function is thread-safe.
 *
 * Signal dispositions are process-wide: if a signal handler is
 * installed, the handler will be invoked in the thread thread, but if
 * the disposition of the signal is "stop", "continue", or "terminate",
 * this action will affect the whole process.
 *
 * POSIX.1-2008 recommends that if an implementation detects the use of
 * a thread ID after the end of its lifetime, pthread_kill() should
 * return the error ESRCH.  The glibc implementation returns this error
 * in the cases where an invalid thread ID can be detected.  But note
 * also that POSIX says that an attempt to use a thread ID whose
 * lifetime has ended produces undefined behavior, and an attempt to use
 * an invalid thread ID in a call to pthread_kill() can, for example,
 * cause a segmentation fault.
 */
		 // pthread_kill( t2, SIGHUP);
		 // pthread_kill( t2, SIGSEGV);
		 pthread_kill( t1, SIGINT);

     pthread_join( t1, (void *)&r1 );
     pthread_join( t2, (void *)&r2 );

     printf("Thread 1 returns: %d\n",r1);
     printf("Thread 2 returns: %d\n",r2);

		 printf("%d! = %d\n",NUMBER,r1*r2);
     exit(0);
}

void *myfn( void *intarray )
{
     int *g = (int *) intarray;
		 int i=0;
		 int d=1;
		
		 for (i=g[0];i<=g[1];i++) {
				d*=i;
				sleep(2);
			}
//     	printf("i=%d .. d=%d\n", i,d);
	
		pthread_exit((void *)d);
}
