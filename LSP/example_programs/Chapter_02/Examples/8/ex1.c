//
//  Take home:  normally - open flags are assigned using open() API
//  					  but you can change flags on an existing/open fd 
//  					  using fcntl() API.
//
// ch2_15.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define 	_POSIX_SOURCE 1

int main() {

	int c=0, fd=0, flags, status;

	flags=fcntl(fd,F_GETFL, 0);
	if (flags == -1) { 
		fprintf(stderr,"fcntl failed ..%d.\n",1);
		exit(1);
	}

	flags |= O_NONBLOCK;
	status=fcntl(fd, F_SETFL, flags);	
	
	while(1) {
		c=getchar();
		if (c==EOF) {
			// test for errno and SIGNALs here ..
		 	fprintf(stderr,"No More Data Available!\n");
			break;
		}
		else
			putchar(c);
		}
	
		flags &= ~O_NONBLOCK;
		status=fcntl(fd, F_SETFL, flags);	
}
