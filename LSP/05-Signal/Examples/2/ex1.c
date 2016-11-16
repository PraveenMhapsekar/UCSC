#include <stdio.h>
#include <signal.h>

void intr_handler(int sig) {
	if (sig==SIGINT)
		fprintf(stderr,"\n Handling Signal: %d\n", sig);

  fprintf(stderr,"Sleep 4secs here\n");
  sleep(4);
}

int main () {

		int i=0;

		signal(SIGINT,intr_handler);

		while(i<10) {
		  printf("Hello from %d .. %d\n", getpid(), i++);
		  sleep(1);
		}
		signal(SIGINT,SIG_DFL);
}
