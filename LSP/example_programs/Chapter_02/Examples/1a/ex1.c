// ch2_1.c

#include <stdio.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	int rfd;

	rfd=open(rfn, O_RDONLY);
	fprintf(stderr,"Got fd==%d.\n", rfd);
	close(rfd);
}
