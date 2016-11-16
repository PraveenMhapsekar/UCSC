#include <stdio.h>

int main() {

	printf("Hello World from PID=%d.\n",getpid());
	fork();
	printf("Hello Again from PID=%d.\n",getpid());

	return 0;
}
