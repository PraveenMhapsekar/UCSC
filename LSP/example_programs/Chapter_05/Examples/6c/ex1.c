// ch5_5.c

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

// #define MYSIGNAL 			SIGINT+9
// #define MYSIGNAL 			SIGRTMIN
// #define MYSIGNAL 			SIGRTMIN+20
#define MYSIGNAL 			SIGRTMIN+12
// #define MYSIGNAL 			SIGHUP   // try kill -1 <pid> multiple times
// #define MYSIGNAL 			SIGRTMAX
// #define MYSIGNAL 			SIGRTMAX-30
// #define MYSIGNAL 			SIGRTMAX-40
// #define MYSIGNAL 			SIGABRT   // #6 .. can be masked / handled
// #define MYSIGNAL 			SIGKILL   // #9 .. cannot be masked / handled
// #define MYSIGNAL 			SIGSEGV   // #11 .. can be masked / handled
// #define MYSIGNAL 			SIGTERM   // #15 .. cannot be masked / handled

void intr_handler(int sig) {
	fprintf(stderr,"\n Handling Signal: %d\n", sig);
}

int main() {
	int c;

	struct sigaction oact, nact;

	nact.sa_handler=intr_handler;
	sigemptyset(&nact.sa_mask);
	nact.sa_flags=SA_RESTART;

	sigaction(MYSIGNAL,&nact,&oact);
	fprintf(stderr, "Enter an input char(PID==%d):\n",getpid());

	while((c=getchar())!=EOF) 
		putchar(c);

	sigaction(MYSIGNAL,&oact,0);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

	exit(0);
}
