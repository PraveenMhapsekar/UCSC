#include <stdio.h>

int main() {
	int c;
	
	printf("Hello World from PID=%d.",getpid());


	fprintf(stderr,"Sleeping 10s. Note that output of prior printf is not displayed till after printf is called again ..\n");	

	sleep(2);

	printf("\nHello Again, World! from PID=%d.\n",getpid());

	return 0;
}
