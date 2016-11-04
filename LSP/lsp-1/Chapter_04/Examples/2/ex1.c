#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

void *myfn( void *fnptr );

main()
{
     pthread_t t1;
     char *s1 = "Thread 1";
		 int c;
     int  r1;

	// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	//                           void *(*start_routine) (void *), void *arg);
     r1 = pthread_create( &t1, NULL, myfn, (void*)s1);

		 // do fun stuff here in main()
		 fprintf(stderr,"Enter a char: ");
		 c=getchar();

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
	int i=0;
	int c=0;

	for (i=0; i++<5;) {
	 	// gettid is not directly supported in glibc. see 'man gettid'
	 	// printf("%d. In %s: My PID=%u, My TID=%u\n",i,msg,getpid(),gettid());
	 	printf("%d. In %s: My PID=%u\n",i,msg,getpid());
    // while(1);
		sleep(1);
	}

	//  fprintf(stderr,"Waiting for a char ... ");
	//	c=getchar();
	
	return;
}
