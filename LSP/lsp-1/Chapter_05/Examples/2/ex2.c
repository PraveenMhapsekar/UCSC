#include <stdio.h>
#include <signal.h>

void intr_handler(int sig) {
		fprintf(stderr,"\n Handling Signal: %d\n", sig);
}

int main () {

		int i=0;

		// signal(SIGKILL,intr_handler); // cannot be handled, masked or ignored
		signal(SIGKILL,SIG_IGN);         // cannot be handled, masked or ignored

		while(i<10) {
		  printf("Hello from %d .. %d\n", getpid(), i++);
		  sleep(1);
		}
		signal(SIGKILL,SIG_DFL);
}
