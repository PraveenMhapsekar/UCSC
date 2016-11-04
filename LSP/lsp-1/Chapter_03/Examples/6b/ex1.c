#include <stdio.h>

int main() {

	fprintf(stderr,"Hello World pid=%d!",(int) getpid() );

	fork();

	printf("Hello from process %d!\n",(int) getpid() );

	return 0;

}
