#include "ex1.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {

	Example ExampleData[1];

	int rfd, i=0, j=0,rc=0;
	int rp=0;	

	umask(0000);

	if ((rfd=open("myserver.dat",O_RDONLY)) < 0) { 
		fprintf(stderr,"open() Failure: %s\n", strerror(errno));
		return -1;
	}

	j=sizeof(Example);	

	switch (argc) {
		case 1:
			while (i<MAXLINES) {
				if ((read(rfd,ExampleData, j)) < j) {
					fprintf(stderr,"read() Failure: %s\n", strerror(errno));
					return -1;
				}

				fprintf(stderr,"%d:%s\n", ExampleData->linenum, ExampleData->data);
				i++;
			}
			break;
		case 2:
			rp=(atoi(argv[1])-1)*sizeof(Example);
			if ((rc=(lseek(rfd, rp, SEEK_SET))) < 0) {
				fprintf(stderr,"lseek() Error: %s(%d)\n", strerror(errno),rc);
				return -1;
			}
  		if ((j=(read(rfd, ExampleData, sizeof(Example)))) <= 0) { 
    		fprintf(stderr,"ERR: LineNum: %d: NOT FOUND\n", rp);
				return -1;
			}
			fprintf(stderr,"%d:%s (%d)\n",ExampleData->linenum,ExampleData->data,rp+1);
			i+=1;
			break;
		default:	
			fprintf(stderr,"Usage:%s [linenum]\n",argv[0]);
			break;
	}

	fprintf(stderr,"Read %d lines.\n",i);

	return 0;
}
