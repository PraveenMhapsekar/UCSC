
#include <stdio.h>

int main() {
	int c;
	
	printf("Hello World from PID=%d.",getpid());


	fprintf(stderr,"Sleeping 10s. Note that output of prior printf is displayed immediately ..");	

	sleep(10);

	printf("Hello Again, World! from PID=%d.",getpid());

	fprintf(stderr,"Enter a char:");
	c=getchar();

	return 0;
}
	

	
