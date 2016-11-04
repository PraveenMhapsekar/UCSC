#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myfn( void *fnptr );

main()
{
     pthread_t t1;
     char *s1 = "Thread 1";
		 int c;
     int  r1;

     r1 = pthread_create( &t1, NULL, myfn, (void*)s1);

		 // do fun stuff here in main()
		 fprintf(stderr,"Enter a char: ");
		 sleep(10);
		 // c=getchar();

		 // ready for the rejoin of the thread
     pthread_join( t1, NULL);

     printf("In Main:Thread 1 returns: %d\n",r1);

		 fprintf(stderr,"Waiting for a char ... ");
		 c=getchar();
     exit(0);
}

void *myfn( void *fnptr )
{
	char *msg = (char *) fnptr;
	pid_t pid;
	int i=0;
		 int c;

	for (i=0; i++<2; ) {
	 	printf("%d. In %s: My PID=%u\n",i,msg,getpid());
		// pid=fork();	
		sleep(1);
		system("ps -mL");
	}

	fprintf(stderr,"PID=%d .. Waiting for a char ... ", getpid());
	c=getchar();
}
