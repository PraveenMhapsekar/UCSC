#include <stdio.h>

int main() {

	printf("Hello World pid=%d with PPID=%d!\n",(int)getpid(),getppid());
	system("ps -f");

	fork();

	printf("Hello from process pid=%d with PPID=%d!\n",(int)getpid(),getppid());

  sleep(1);
	return 0;
}
