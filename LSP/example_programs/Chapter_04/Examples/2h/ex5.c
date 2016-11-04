// r1, r2 are local variables; however, return from pthread_exit uses global variables

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER 9

void *myfn( void *fnptr );

int  d[2];

main()
{
     pthread_t t1, t2;
     int i1[] = {1,NUMBER/2};
     int i2[] = {(NUMBER/2)+1,NUMBER};
		 int i=0;
		 int r1,r2;

		 int status;

		 while (i<2) d[i++]=1;
     r1 = pthread_create( &t1, NULL, myfn, (void*)i1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)i2);

     pthread_join( t1, (void *)&r1 );
     pthread_join( t2, (void *)&r2 );

     printf("Thread 1 returns: %d\n",r1);
     printf("Thread 2 returns: %d\n",r2);

		 printf("%d! = %d\n",NUMBER,r1*r2);

		 return 0;

}

void *myfn( void *intarray )
{
     int *g = (int *) intarray;
		 int i=0;
		 int s=(g[0]==1) ? 0 : 1;
		 // int d=1;  // watch for local variable issue, here.
		
		 for (i=g[0];i<=g[1];i++) 
				d[s]*=i;
     	// printf("i=%d .. d[%d]=%d\n", i,s,d);
	
		pthread_exit((void *)d[s]);
}
