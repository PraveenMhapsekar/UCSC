#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <unistd.h>
#include <string.h>

#define TMOUT 5

int
main(void) {
    struct pollfd pollfd[1];
    int retval;

		int c;

		int myfd1=STDIN_FILENO;

	 memset(pollfd, 0,sizeof(struct pollfd));
   pollfd->fd=myfd1;
	 pollfd->events |= POLLIN;

	 fprintf(stderr,"Enter a char: (TIMEOUT=%d): ",TMOUT);
 	 retval = poll(pollfd,1,TMOUT*1000); // 5s timeout
// retval = poll(pollfd,1,-1); // -1 signifies infinite timeout

   if (retval == -1)
        perror("select()");
    else if (retval)
        printf("Data (#fd's=%d) is available now.\n", retval);
				// (pollfd->revents & POLLIN)  or (pollfd->revents & POLLOUT)
    else
        printf("No data within '%d' seconds.\n",TMOUT);

   return 0;
}
