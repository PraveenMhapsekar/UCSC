// ch2_16.c

#define _POSIX_SOURCE 1

#define TIMEOUTVALUE 5

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MYSTR "Hello World!\n"

int main(int argc, char **argv) {
	
	char str[128];
	struct pollfd pollfd[1];

	int myfd1 = STDIN_FILENO;
	int num=0,len,wlen;

// while (1) {

	 	memset(pollfd, 0, sizeof(struct pollfd));  // zero'd pollfd 
		pollfd->fd=myfd1;               // init 
		pollfd->events |= POLLIN | POLLOUT;      // init 


			// int poll(struct pollfd *fds, nfds_t nfds, int timeout);
/*
			The timeout argument specifies an upper limit on the time for which poll() will block, in milliseconds. Specifying a negative value in timeout means an infinite timeout. 
*/
		  if ((num = poll(pollfd,1,-1)) < 0) {
    		fprintf(stderr,"ERR:on poll():%s\n",strerror(errno));
    		exit(1);
  		}
  		else if (num) {   // poll() returned an event

    		memset(str,0,sizeof(str));

    		if (pollfd->revents & POLLOUT) {

      		// write
      		strcpy(str, MYSTR);
      		wlen = strlen(str);
      		if ((len = write(pollfd->fd, str, wlen)) == -1) {
        		fprintf(stderr,"ERR:on write():%s\n",strerror(errno));
        		exit(1);
      		}
    		}
	
    		if(pollfd->revents & POLLIN) {
	
      	// read .. can use "while" loop to "consume" chars
      		if ((len = read(pollfd->fd, str, sizeof(str))) == -1) {
        		fprintf(stderr,"ERR:on read():%s\n",strerror(errno));
        		exit(1);
					}
				}
		}
	// }

	exit(0);
}
