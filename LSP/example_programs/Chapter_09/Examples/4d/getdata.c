#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINES 3

typedef struct {
  int linenum;
  char data[50];
} Example;

int main() {

	Example ExampleData[1];

	int rfd, i=1, j=0;

	umask(0000);

	if ((rfd=open("myserver.dat",O_RDONLY)) < 0) { 
		fprintf(stderr,"open() Failure: %s\n", strerror(errno));
		return -1;
	}

	j=sizeof(Example);	

	while (i<=MAXLINES) {

		if ((read(rfd,ExampleData, j)) < j) {
			fprintf(stderr,"write() Failure: %s\n", strerror(errno));
			return -1;
		}

		fprintf(stderr,"%d:%s\n", 
			ExampleData->linenum, ExampleData->data);
		i++;
	}

	fprintf(stderr,"Read %d lines.\n",i-1);

	return 0;
}
