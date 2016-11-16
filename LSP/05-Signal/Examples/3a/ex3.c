
// ch5_6.c

#include <stdio.h>
#include <signal.h>
#include <errno.h>

#ifndef SA_RESTART
# 	define SA_RESTART 0x00000004
#endif

void intr_handler(int sig) {
	fprintf(stderr,"\n Handling Signal: (PID==%d)  %d\n", sig,getpid());
}

int main() {
	int c;

	struct sigaction oact, act;

	act.sa_handler=intr_handler;
	sigemptyset(&act.sa_mask);
	// act.sa_flags=SA_RESTART;

	sigaction(SIGINT,&act,&oact);
	fprintf(stderr, "Enter an input char (PID==%d):\n",getpid());

#ifdef __SYSV__
	while(1) {
		errno=0;

		if ((c=getchar())==EOF) {
			if (errno==EINTR) {
				
				fprintf(stderr, "EOF and EINTR -> SYSV\n");
				fprintf(stderr, "Enter an input char(SYS V):\n");
				continue;
			}
			break;
		}
		putchar(c);
	}
#else
	while ((c=getchar())!=EOF)
		putchar(c);
#endif

	sigaction(SIGINT,&oact,0);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");
}
