// Take Home:  select() very heavily used in socket programming.
// 						 it facilitates an asynchronous/interrupt-driven model 
// 						 for notification of IO on an fd.
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

int main(int argc, char **argv) {
	fd_set rfd,wfd,efd;
	struct timeval tmout;

	int myfd1 = STDIN_FILENO;
	int myfd2 = 0;
	int maxfd = 0;
	int nrdy = 0, c = 0;

	while (1) {
		tmout.tv_sec=TIMEOUTVALUE;
		tmout.tv_usec=1000;

		FD_ZERO(&rfd);
		FD_ZERO(&wfd);
		FD_ZERO(&efd);
		
		FD_SET(myfd1,&rfd);
		FD_SET(myfd2,&rfd);

		maxfd=1;
		nrdy = select (maxfd, &rfd, &wfd, &efd, &tmout);

		fprintf(stderr,"After Select ..\n");

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
