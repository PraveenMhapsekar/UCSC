// ch2_1.c

#include <stdio.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	int rfd;

	int oflag=O_WRONLY;

	rfd=open(rfn, oflag);
	fprintf(stderr,"Got fd==%d (oflag==%d)\n", rfd,oflag);
	close(rfd);
}
