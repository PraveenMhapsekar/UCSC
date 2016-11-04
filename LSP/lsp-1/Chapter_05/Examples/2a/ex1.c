#include <stdio.h>
#include <signal.h>
#include <errno.h>

void intr_handler(int sig) {
	fprintf(stderr,"\n Handling Signal: %d\n", sig);
}

int main() {
	int c;

	signal(SIGINT,intr_handler);
	fprintf(stderr, 
		"Enter an input char .. PID=%d (including ^C - for Handler):\n",
		getpid()
	);

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	signal(SIGINT,SIG_DFL);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

	return 0;
}
