#include <stdio.h>

int main() {

	fprintf(stderr,"Hello World from PID=%d.",getpid());

	fork();

	printf("Hello Again from PID=%d.\n",getpid());

	return 0;
}
