#include <stdio.h>
#include <signal.h>
#include <errno.h>
#ifdef __SYSV__
	#ifndef SA_RESTART
	# define SA_RESTART 0x00000004
	#endif
#endif

void intr_handler(int sig) { // Handler code
	int c=0;
	fprintf(stderr,"\nHandling Signal: %d\nEnter a char:",sig);

	c=getchar();
}

int main(int argc, char **argv) {
	int c;
	struct sigaction oact, act;

	act.sa_handler = intr_handler; // set handler info

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGHUP);
	sigaddset(&act.sa_mask, SIGTSTP);

	act.sa_flags = SA_RESTART;

	sigaction(SIGINT, &act, &oact); // set signal handler

	fprintf(stderr, "Enter an input char(PID==%d):\n", getpid());

	while((c=getchar())!=EOF) { 
		putchar(c);
	}

	sigaction(SIGINT, &oact, 0); // reset signal info
	fprintf(stderr, "EOF Entered:\n"); // end program
}
