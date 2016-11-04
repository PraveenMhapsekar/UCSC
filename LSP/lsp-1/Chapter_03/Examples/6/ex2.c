#include <stdio.h>

int main() {

	printf("Hello World pid=%d with PPID=%d!",(int)getpid(),getppid());
	// system("ps -f");

	fork();

	// while(1);

	printf("\nHello from process pid=%d with PPID=%d!\n",(int)getpid(),getppid());

  sleep(1);
	return 0;
}
