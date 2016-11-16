// ch5_5.c

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

void intr_handler(int sig) {
	fprintf(stderr,"\n Handling Signal: %d\n", sig);
}

int main() {
	int c;

	struct sigaction oact, nact;

	nact.sa_handler=intr_handler;
	sigemptyset(&nact.sa_mask);
	nact.sa_flags=0;
	// nact.sa_flags=SA_RESTART;

	sigaction(SIGINT,&nact,&oact);
	fprintf(stderr, "PID==%d .. Enter an input char:\n", getpid());

#ifdef SYSV
	while(1) {
		errno=0;

		if ((c=getchar())==EOF) {
			if (errno==EINTR) {
				
				fprintf(stderr, "EOF and EINTR -> SYSV\n");
				fprintf(stderr, "Enter an input char:\n");
				continue;
			}
			break;
		}
		putchar(c);
	}
#else
	while((c=getchar())!=EOF) 
		putchar(c);
#endif

	sigaction(SIGINT,&oact,0);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

	exit(0);
	// return 0;
}
