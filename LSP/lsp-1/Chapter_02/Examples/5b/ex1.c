#include <stdio.h>

int main() {
	int c;
	
	fprintf(stderr, "Hello World from PID=%d.",getpid());


	sleep(10);


	fprintf(stderr,"Sleeping 10s. Note that output of prior printf is displayed immediately ..\n");	

	printf("\nHello Again, World! from PID=%d.\n",getpid());

	return 0;
}
