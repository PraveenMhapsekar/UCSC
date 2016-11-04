#include <stdio.h>

int main() {
	int c;
	
	printf("Hello World from PID=%d.",getpid());

	sleep(5);

	printf("\nHello Again, World! from PID=%d.\n",getpid());

	return 0;
}
