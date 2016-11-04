#include <stdio.h>

int main() {

  int pidt=-1;

	printf("Hello World pid=%d with PPID=%d!\n",(int)getpid(),getppid());
	system("ps -f");

	pidt=fork();

	printf("Hello from PID=%d with PPID=%d - fork()==%d.!\n",(int)getpid(),getppid(),pidt);

  sleep(1);
	return 0;
}
