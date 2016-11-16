#include <stdio.h>
#include <signal.h>
#include <errno.h>

void intr_handler(int sig) {
	int c=0;
	// to handle problem#1 on pg 16.
	signal(sig, SIG_IGN);

	fprintf(stderr,"\n Handling Signal: %d\n", sig);
  c=getchar();
	// to handle problem#2 on pg 16.
	signal(sig, intr_handler);
}

int main() {
	int c;

	signal(SIGINT,intr_handler);
	// signal(SIGKILL,intr_handler); // cannot be masked, ignored or handled
	fprintf(stderr, "Enter an input char: PID==%d\n", getpid());

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	signal(SIGINT,SIG_DFL);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

	return 0;
}
