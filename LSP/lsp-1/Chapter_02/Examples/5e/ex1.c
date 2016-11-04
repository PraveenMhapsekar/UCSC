#include <stdio.h>

int main() {
	int c;
	
	fprintf(stderr,"Hello World from PID=%d.",getpid());

	fprintf(stderr,"Sleeping 10s. Note that output of prior printf was displayed ..\n");	

	sleep(10);

	printf("Hello Again, World! from PID=%d.\n",getpid());

	return 0;
}
