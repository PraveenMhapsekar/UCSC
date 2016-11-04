#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER 16

void *myfn( void *fnptr );

int d[3];

main()
{
     static int  r1, r2, r3;

     pthread_t t1, t2, t3;
     int i1[] = {1,NUMBER/2};
     int i2[] = {(NUMBER/2)+1,NUMBER};
     int i3[] = {1,NUMBER};

		 int i=0;
		 int status;

		 while (i<3) d[i++]=1;

     r1 = pthread_create( &t1, NULL, myfn, (void*)i1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)i2);
     r3 = pthread_create( &t3, NULL, myfn, (void*)i3);

     pthread_join( t1, (void *)&r1 );
     pthread_join( t2, (void *)&r2 );
     // pthread_join( t3, (void *)&r3 );

     printf("Thread 1 returns: %d\n",r1);
     printf("Thread 2 returns: %d\n",r2);
     // printf("Thread 3 returns: %d\n",r3);

		 // pthread_kill

		 printf("%d! = %d\n",NUMBER,r1*r2);
     exit(0);

}

void *myfn( void *intarray )
{
     int *g = (int *) intarray;
		 int i=0;
		 int s=((g[0]==1)&&(g[1]<NUMBER))?0:((g[0]>1)&&(g[1]==NUMBER))?1:2;
		
		 for (i=g[0];i<=g[1];i++) 
				d[s]*=i;
		 // printf("i=%d .. d=%d\n", i,d);
	
		pthread_exit((void *)d[s]);
}
