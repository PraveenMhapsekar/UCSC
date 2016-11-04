#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
		 void *status;

	 	 sleep(2);

     r1 = pthread_create( &t1, NULL, myfn, (void*)s1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)s2);
     r3 = pthread_create( &t3, NULL, myfn, (void*)s3);

     r1j=pthread_join( t1, NULL);
     r2j=pthread_join( t2, NULL);
     r3j=pthread_join( t3, &status);

     printf("In main: Thread 1 returns: %d,%d\n",r1,r1j);
     printf("In main: Thread 2 returns: %d,%d\n",r2,r2j);
     printf("In main: Thread 3 returns: %d,%d,%d\n",r3,r3j,(int) status);
     exit(0);

}

void *myfn( void *fnptr )
{
	 static int i=0; // static variable.
   pthread_t tid=pthread_self();
	 char *msg = (char *) fnptr;

	// pthread_equal returns 1 for match, else 0
 	if (pthread_equal(tid,t3)) 
	{
	 	printf("Bailing out in t3\n");
		pthread_exit((void *)st);
	}

	while (i++<12) 
	{
	 	printf("In %s(i==%d): TID=%u and PID=%u\n",msg,i,tid,getpid());
	 	sleep(1);
	}
}	
