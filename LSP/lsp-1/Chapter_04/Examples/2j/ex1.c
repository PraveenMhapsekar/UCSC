#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// #define DEBUG 1
#define DEBUG 0

#define NUMBER 8

void *myfn( void *fnptr );

main()
{
     pthread_t t1, t2;
     int i1[] = {1,(NUMBER/2)};
     int i2[] = {(NUMBER/2)+1,NUMBER};
     int  r1, r2, r3, i=1, j=1;

     r1 = pthread_create( &t1, NULL, myfn, (void*)i1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)i2);

     pthread_join( t1, (void **) (int *)&r1);
     pthread_join( t2, (void **) (int *)&r2);

     printf("Thread 1 returns: %d\n",r1);
     printf("Thread 2 returns: %d\n",r2);

		 printf("Factorial(%d)=%d\n",NUMBER,r1 * r2);
	
		// confirm
		for (i=1;++i<=NUMBER;) j*=i;
			
		 printf("Confirm: Factorial(%d)=%d\n",NUMBER,j);

     exit(0);
}

void *myfn( void *fnptr )
{
     int *g = (int *) fnptr;
		 int i=0;
		 int d=1;
		
		 for (i=g[0];i<=g[1];i++) {
			d*=i;
			if(DEBUG)
	     	printf("i=%d .. d=%d\n", i,d);
		}
		
		return (int *)d;
}
