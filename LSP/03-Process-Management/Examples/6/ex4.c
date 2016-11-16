#include <stdio.h>
#include <string.h>

int main() {
	
	int pidt;

	printf("Hello World pid=%d!\n",(int) getpid() );

	pidt=fork();

	printf("Hello from %s process %d!\n",
		(pidt)?"Parent":"Child",
		(int) getpid() );

	return 0;

}
