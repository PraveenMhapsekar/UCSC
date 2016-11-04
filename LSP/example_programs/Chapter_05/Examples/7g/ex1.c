#define ALARMTMOUT 5
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <unistd.h>
#include <string.h>

int
main(void) {
    struct pollfd pollfd[1];
    struct timeval tv;
    int retval;
		int myfd1=STDIN_FILENO;

		int c;


		alarm(ALARMTMOUT);



	 	memset(pollfd, 0,sizeof(struct pollfd));
   	pollfd->fd=myfd1;
	 	pollfd->events |= POLLIN;

   	retval = poll(pollfd,1,-1); // -1 indicates infinite timeout

   	if (retval == -1)
    	perror("select()");
    else if (retval)
			printf("Data (#fd's=%d) is available now.\n", retval);
			// (pollfd->revents & POLLIN)  or (pollfd->revents & POLLOUT)
    else
			printf("No data within five seconds.\n");

	 c=getchar();
   return 0;
}
