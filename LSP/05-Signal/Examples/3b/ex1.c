// ch5_7.c

// #define _POSIX_SOURCE 1
#include <stdio.h>
#include <signal.h>
#include <errno.h>
/*
#ifdef __SYSV__
/* */
	#ifndef SA_RESTART
	# 	define SA_RESTART 0x00000004
	#endif
/*
#endif
*/

void intr_handler(int sig) {
	int c;
	fprintf(stderr,"\n Handling Signal: %d\n", sig);
	fprintf(stderr, "Enter an input char (in Handler):\n");

	c=getchar();

	fprintf(stderr, "The char you entered is '%c':", c);
}

int main() {
	int c;

	struct sigaction oact, act;

	act.sa_handler=intr_handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGTSTP);
	act.sa_flags=SA_RESTART;

/*
#ifdef __SYSV__
	act.sa_flags=SA_RESTART;
#endif
*/

	sigaction(SIGINT,&act,&oact);
	fprintf(stderr, "Enter an input char (PID==%d):\n", getpid());

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
	while ((c=getchar())!=EOF)
		putchar(c);
#endif

	sigaction(SIGINT,&oact,0);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

  return 0;
}
