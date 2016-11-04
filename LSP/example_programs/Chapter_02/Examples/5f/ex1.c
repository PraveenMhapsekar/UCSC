#include <stdio.h>

int main() {
	int c;
	
	fprintf(stderr,"Hello World from PID=%d.",getpid());
	fprintf(stdout,"\nSleeping 10s. Note that output of prior printf is displayed prior to sleep()\n");
	sleep(2);
	fprintf(stderr,"\nHello Again, World! from PID=%d.\n",getpid());

  fprintf(stderr,"Enter any char");
  c=getchar();

	return 0;
}
	

	
