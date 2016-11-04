#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *myfn( void *fnptr );
int c;

main()
{
     pthread_t t1, t2;
     char *s1 = "Thread 1";
     char *s2 = "Thread 2";

		 char m[50];
     int  r1, r2;

     r1 = pthread_create( &t1, NULL, myfn, (void*)s1);
     r2 = pthread_create( &t2, NULL, myfn, (void*)s2);

		 // fprintf(stderr,"Enter a char: ");
		 // c=getchar();
		 myfn("In Main");

	   sleep (2);
		 sprintf(m,"%s %d","pmap",getpid());
		 system(m); 
		 
		 fprintf(stderr, "Enter a char:");
		 c=getchar();
		 
     pthread_join( t1, NULL);
     pthread_join( t2, NULL);

     printf("In Main:Thread 1 returns: %d\n",r1);
     printf("In Main:Thread 2 returns: %d\n",r2);

		 fprintf(stderr,"Waiting for a char ... ");
		 c=getchar();
     exit(0);
}

void *myfn( void *fnptr )
{
	char *msg = (char *) fnptr;
	int i=0;

	for (i=0; i++<2; ) {
	 	printf("%d. In %s: My PID=%u\n",i,msg,getpid());
		sleep(1);
	}

	//  fprintf(stderr,"Waiting for a char ... ");
	c=getchar();
}
