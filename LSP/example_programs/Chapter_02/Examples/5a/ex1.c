#include <stdio.h>

int main() {
	int c;
	
	fprintf(stderr, "Hello World from PID=%d.",getpid());
	sleep(10);
	printf("\nHello Again, World! from PID=%d.\n",getpid());

	return 0;
}
