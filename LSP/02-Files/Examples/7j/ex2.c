
// ch2_13.c

#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

char *rfn= "myfile.txt";

int main(int argc, char **argv) {
	int c,newfd;

	if (argc == 2) {
		rfn=argv[1];
 	}

	fprintf(stderr, "Reading a char from stdin\n");
	c=getchar();
	fprintf(stderr, "char read is %c\n", c);

	newfd=open(rfn,O_RDONLY);

	if (newfd < 0) {
		fprintf(stderr, "Error: open %s failed:%s", rfn,strerror(errno));
		exit(1);
	}

	fprintf(stderr, "File '%s' uses fd=%d.\n", rfn, newfd);

	if (dup2(newfd,0) != 0) {  // will go into slot 0
		fprintf(stderr, "Error: Could not dup file %s", rfn);
		exit(1);
	}

	close(newfd);  // close fd==3

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	close(0);
	exit(0);
}
