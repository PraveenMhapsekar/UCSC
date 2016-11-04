#include <stdio.h>

int main() {
	int c;
	
	printf("Hello World from PID=%d.",getpid());

	sleep(2);

	printf("Hello Again, World! from PID=%d.",getpid());

	while(1);
	return 0;
}
