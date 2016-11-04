#include <stdio.h>
#include <unistd.h>

int main() {

	printf("Before fork .. Hello World\n");

	fork();

	printf("After fork .. Hello World = %d\n", getpid());

	return 0;
}
	
