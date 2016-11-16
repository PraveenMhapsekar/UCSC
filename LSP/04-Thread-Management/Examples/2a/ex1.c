#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *myfn( void *fnptr );

main()
{
     pthread_t t[4];
     char *s1 = "Thread 1";
     char *s2 = "Thread 2";
     char *s3 = "Thread 3";
     char *s4 = "Thread 4";
     int  r[4];
		 int i=0;

		 printf(" main() resides at %#0x, while myfn() resides at %#0x\n", main, myfn); 

     r[i] = pthread_create( &t[i], NULL, myfn, (void*)s1);
     i++; r[i] = pthread_create( &t[i], NULL, myfn, (void*)s2);
     i++; r[i] = pthread_create( &t[i], NULL, myfn, (void*)s3);
     i++; r[i] = pthread_create( &t[i], NULL, myfn, (void*)s4);

		 i=0;
     pthread_join( t[i], NULL);
     i++; pthread_join( t[i], NULL);
     i++; pthread_join( t[i], NULL);
     i++; pthread_join( t[i], NULL);

		 i=0;
     printf("In Main:Thread %d returns: %d\n",i,r[i]);
     i++; printf("In Main:Thread %d returns: %d\n",i,r[i]);
     i++; printf("In Main:Thread %d returns: %d\n",i,r[i]);
     i++; printf("In Main:Thread %d returns: %d\n",i,r[i]);
     exit(0);

}

void *myfn( void *fnarg )
{
	 char *msg = (char *) fnarg;

	 printf("Before Sleep: In %s: My PID=%u\n",msg,getpid());

	 sleep(5);

	 printf("After Sleep: In %s: My PID=%u\n",msg,getpid());
}
