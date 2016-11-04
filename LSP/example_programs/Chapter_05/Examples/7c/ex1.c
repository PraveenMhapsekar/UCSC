#define TIMEOUT_TIMEDIO 5



#define BUFSZ 512
#define ERRBUFSZ 512

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <setjmp.h>

#ifndef SA_RESTART
	#define SA_RESTART 0x000004
#endif

static sigjmp_buf jmpbuf;

int timed_io(char *buf, int len, FILE *rfp, int sec);
static void sigalrm_handler(int signo);

static void sigalrm_handler(int signo) {
	siglongjmp(jmpbuf,1);
}

int timed_io(char *buf, int len, FILE *rfp, int sec) {

	struct sigaction nsigaction[1];
	struct sigaction osigaction[1];

	int prev_alrm;
	int st=0; 	/* if st == -1 at EOF; st == -2 Time Out reached; */
	
	if (sigsetjmp(jmpbuf,1) == 0) {
		nsigaction->sa_handler=sigalrm_handler;
		sigemptyset(&nsigaction->sa_mask);
		nsigaction->sa_flags = SA_RESTART;

		prev_alrm=alarm(0);
		sigaction(SIGALRM,nsigaction,osigaction);
	
		alarm(sec);

		if (fgets(buf,len,rfp)==NULL) {
			st=-1;
		}
		buf[strlen(buf)-1]=0;
	}
	else {
		st=-2;
	}

	alarm(0);	/* reset old alarm and handler */
	sigaction(SIGALRM,osigaction,0);
	alarm(prev_alrm);

	return st;
}
	
int main(int argc, char **argv) {
	int st;
	int sec=TIMEOUT_TIMEDIO;
	char *buf=(char *)malloc(BUFSZ*sizeof(char)); 
	char *errbuf=(char *)malloc(ERRBUFSZ*sizeof(char)); 

	fprintf(stderr,"Enter Input (%d sec):",TIMEOUT_TIMEDIO);

	st=timed_io(buf, BUFSZ, stdin, sec);
	if (st !=0) {
		fprintf(stderr,"ERR: No Input: %s (Status=%d)\n", errbuf,st);
		return -1;
	}
	else {
		fprintf(stderr,"Input Buf=\"%s\" (Len=%d).\n",buf, strlen(buf));
	}

	exit(0);
}
