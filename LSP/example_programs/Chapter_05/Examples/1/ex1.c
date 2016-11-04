// ch5_1.c

#include <stdio.h>
#include <pthread.h>

int main() 
{

	int c=5;

	// fprintf(stderr," Address of main is %x\n", main);
	fprintf(stderr," Address of main is %#x\n", main);
	fprintf(stderr," Address of main is %p\n", main);

	fprintf(stderr," pthread_self() is %#x\n", pthread_self);

	fprintf(stderr," Address of printf is %p\n", printf);
	// fprintf(stderr," pthread_self() is %#x\n", pthread_self());
	// fprintf(stderr," pthread_self() is %#x\n", pthread_exit());  // :-)

	fprintf(stderr,"Awaiting Input: PID=%d", getpid());
	c=getchar();

	return 0;
}
