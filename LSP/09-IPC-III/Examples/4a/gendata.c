#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MAXLINES 3

typedef struct {
	int linenum;
	char data[50];
} Example;

int main() {

	Example ExampleData[1];

	int wfd, i=1, j=0;

	umask(0000);

	if ((wfd=open("myserver.dat",O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU|S_IRWXG)) < 0) { 
		fprintf(stderr,"open() Failure: %s\n", strerror(errno));
		return -1;
	}

	while (i<=MAXLINES) {
		ExampleData->linenum=i;
		ExampleData->data[0]=0;
		sprintf(ExampleData->data,"This is test line %d.", i);

		j=sizeof(Example);	
		if ((write(wfd,ExampleData, j)) < j) {
			fprintf(stderr,"write() Failure: %s\n", strerror(errno));
			return -1;
		}
		i++;
	}

	fprintf(stderr,"Wrote %d lines.\n",i-1);

	return 0;
}
