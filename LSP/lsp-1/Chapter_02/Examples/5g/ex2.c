#include <stdio.h>

int main() {

	printf("Hello World from PID=%d.",getpid());
	fork();
	printf("Hello Again from PID=%d.\n",getpid());

	return 0;
}
