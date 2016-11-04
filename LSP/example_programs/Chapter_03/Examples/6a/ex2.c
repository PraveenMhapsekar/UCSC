#include <stdio.h>

int main() {

  int pidt=0;

	printf("Hello World pid=%d!",(int) getpid() );

	pidt=fork();

	printf("Hello from process %d!\n",(int) getpid() );

	return 0;

}
