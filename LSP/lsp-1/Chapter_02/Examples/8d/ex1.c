// ch2_16.c

#define _POSIX_SOURCE 1

#define TIMEOUTVALUE 5


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define _XOPEN_SOURCE 600
#include <sys/select.h>

/*
int pselect(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, const struct timespec *timeout,
            const sigset_t *sigmask);

The operation of select() and pselect() is identical, with three differences:

(i) select() uses a timeout that is a struct timeval (with seconds and microseconds), while pselect() uses a struct timespec (with seconds and nanoseconds).

(ii) select() may update the timeout argument to indicate how much time was left. pselect() does not change this argument.

(iii) select() has no sigmask argument, and behaves as pselect() called with NULL sigmask. 
*/

int main(int argc, char **argv) {
	fd_set rfd,wfd,efd;
	struct timespec tmout;

	int myfd1 = STDIN_FILENO;
	int myfd2 = 0;
	int maxfd = 0;
	int nrdy = 0, c = 0;

	while (1) {
		tmout.tv_sec=TIMEOUTVALUE;
		tmout.tv_nsec=1000;

		FD_ZERO(&rfd);
		FD_ZERO(&wfd);
		FD_ZERO(&efd);
		
		FD_SET(myfd1,&rfd);
		FD_SET(myfd2,&rfd);

		maxfd=1;
		nrdy = pselect (maxfd, &rfd, &wfd, &efd, &tmout,NULL);
		if (nrdy<0){
			if(errno==EINTR) {
				continue; // select() not restarted, after 
				// an interrupt.
			}
  		fprintf(stderr,"select() failed: %s\n", strerror(errno));
		}
 
		if (nrdy == 0) {
			fprintf(stderr, "Timed Out.\n");
			break;
		}

		if (FD_ISSET(myfd1,&rfd)) {  
			fprintf(stderr, "Can Read from fd=%d", myfd1);

 			while ((c=getchar()) != EOF) {
       		if (c=='\n') break;
			}

			if (c==EOF) break;
		}
  }

	exit(0);
}
