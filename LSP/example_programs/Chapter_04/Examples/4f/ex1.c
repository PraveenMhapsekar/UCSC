// pthread_yield() + VARIABLE_CLASS variables

#define THREAD1 "Thread #1"
#define THREAD2 "Thread #2"
#define THREAD3 "Thread #3"

#define ITERS 2
#define TRIES 3

#define VARIABLE_CLASS	auto

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *fn();
void *fn2();
void *fn3();
void *fn4();
int  counter = 0;

pthread_t t3;

int main()
{
   int retval1, retval2, retval3;
   pthread_t t1, t2;

   if( (retval1=pthread_create( &t1,NULL,&fn,THREAD1)) ) 
      printf("Thread creation failed: %d\n", retval1);

   if( (retval2=pthread_create( &t2,NULL,&fn,THREAD2)) ) 
      printf("Thread creation failed: %d\n", retval2);

   if( (retval3=pthread_create( &t3,NULL,&fn,THREAD3)) ) 
      printf("Thread creation failed: %d\n", retval3);

   pthread_join(t1,NULL);
   pthread_join(t2,NULL);
   pthread_join(t3,NULL);

	printf("\n");
	counter=0;

   if( (retval1=pthread_create( &t1,NULL,&fn2,THREAD1)) ) 
      printf("Thread creation failed: %d\n", retval1);

   if( (retval2=pthread_create( &t2,NULL,&fn2,THREAD2)) ) 
      printf("Thread creation failed: %d\n", retval2);

   if( (retval3=pthread_create( &t3,NULL,&fn2,THREAD3)) ) 
      printf("Thread creation failed: %d\n", retval3);

   pthread_join(t1,NULL);
   pthread_join(t2,NULL);
   pthread_join(t3,NULL);

	printf("\n");
	counter=0;

   if( (retval1=pthread_create( &t1,NULL,&fn3,THREAD1)) ) 
      printf("Thread creation failed: %d\n", retval1);

   if( (retval2=pthread_create( &t2,NULL,&fn3,THREAD2)) ) 
      printf("Thread creation failed: %d\n", retval2);

   if( (retval3=pthread_create( &t3,NULL,&fn3,THREAD3)) ) 
      printf("Thread creation failed: %d\n", retval3);

   pthread_join(t1,NULL);
   pthread_join(t2,NULL);
   pthread_join(t3,NULL);

	printf("\n");
	counter=0;

   if( (retval1=pthread_create( &t1,NULL,&fn4,THREAD1)) ) 
      printf("Thread creation failed: %d\n", retval1);

   if( (retval2=pthread_create( &t2,NULL,&fn4,THREAD2)) ) 
      printf("Thread creation failed: %d\n", retval2);

   if( (retval3=pthread_create( &t3,NULL,&fn4,THREAD3)) ) 
      printf("Thread creation failed: %d\n", retval3);

   pthread_join(t1,NULL);
   pthread_join(t2,NULL);
   pthread_join(t3,NULL);

	exit(0);
}

void *fn(void *th)
{
	VARIABLE_CLASS int i=0;		// auto class variable to thread stack
	printf("%s",(counter==0) ? "With pthread_yield() for #3\n" : "");

	while (++i<=TRIES*ITERS) 
	{
		fprintf(stdout,"%s -> %u\n", th,i);
		if (pthread_equal(t3,pthread_self()))  {
			fprintf(stdout,"Yield %s -> %d\n", th,i);
			pthread_yield();  // not a return.  instead it is a pause of "indeterminate" duration
	  }

		counter++;
  	printf("%s: Inside fn(): Thread '%u' Counter value: %u.\n",
			(char *) th,pthread_self(),counter);
		  sleep(1);
	}
}

void *fn2(void *th)
{
	VARIABLE_CLASS int i=0;		// auto class variable to thread stack
	printf("%s",(counter==0) ? "Without pthread_yield() for #3\n" : "");

	while (++i<=TRIES*ITERS) {
		if (pthread_equal(t3,pthread_self()))  {
//			pthread_yield();
	  }

		counter++;
  	printf("%s: Inside fn(): Thread '%u' Counter value: %u.\n",
			(char *) th,pthread_self(),counter);
		sleep(1);
	}
}

void *fn3(void *th)
{
	VARIABLE_CLASS int i=0;		// local variable to thread stack
	printf("%s",(counter==0) ? "Again, with pthread_yield() for #3\n" : "");
	while (++i<=TRIES*ITERS) {
		if (pthread_equal(t3,pthread_self()))  {
			pthread_yield();
	  }

		counter++;
  	printf("%s: Inside fn(): Thread '%u' Counter value: %u.\n",
			(char *) th,pthread_self(),counter);
		sleep(1);
	}
}

void *fn4(void *th)
{
	VARIABLE_CLASS int i=0;		// local variable to thread stack
	printf("%s",(counter==0) ? "Again, without pthread_yield() for #3\n" : "");

	while (++i<=TRIES*ITERS) {
		if (pthread_equal(t3,pthread_self()))  {
//			pthread_yield();
	  }

		counter++;
  	printf("%s: Inside fn(): Thread '%u' Counter value: %u.\n",
			(char *) th,pthread_self(),counter);
		sleep(1);
	}
}
