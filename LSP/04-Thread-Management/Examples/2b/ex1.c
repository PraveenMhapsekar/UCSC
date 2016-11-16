#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *myfn( void *fnptr );

main()
{
     pthread_t t1, t2;
     char *s1 = "Thread 1";
     char *s2 = "Thread 2";
     int  r1, r2;

     r1 = pthread_create( &t1, NULL, myfn, (void*)s1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)s2);

     printf("In main: main() is doing some useful work ... t1==%u(%0#x), t2=%u(%0#x)\n", 
			t1,t1,t2,t2);

     pthread_join( t1, NULL);
     pthread_join( t2, NULL);

     printf("In main: Thread 1 returns: %d\n",r1);
     printf("In main: Thread 2 returns: %d\n",r2);
     exit(0);

}

void *myfn( void *fnptr )
{
   pthread_t tid=pthread_self();
	 char *msg = (char *) fnptr;
	 int i=0;

	while(i++<=5) {	
	 	printf("In %s: TID=%u(%0#x) and PID=%u\n",msg, tid,tid,getpid());
		sleep(1);
	}
}
