// ch5_6.c

#include <stdio.h>
#include <signal.h>
#include <errno.h>

void intr_handler(int sig) {
	fprintf(stderr,"\n Handling Signal: %d\n", sig);
}

int main() {
	int c;

	struct sigaction oact, act;

	act.sa_handler=intr_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_RESTART;
	

	sigaction(SIGINT,&act,&oact);
	fprintf(stderr, "Enter an input char:\n");

	while ((c=getchar())!=EOF)
		putchar(c);

	sigaction(SIGINT,&oact,0);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");
}
