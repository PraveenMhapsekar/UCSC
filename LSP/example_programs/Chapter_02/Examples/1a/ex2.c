// ch2_1.c

#include <stdio.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	int rfd;

	rfd=open(rfn, O_RDONLY);
  if (rfd<0) 
		perror("myfile.txt:");

	fprintf(stderr,"Got fd==%d.\n", rfd);
	close(rfd);
}
