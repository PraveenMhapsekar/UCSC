#define   _POSIX_SOURCE 1

#define FILESIZE 16*1024*1024
#define BLK 2*1024*1024

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
	char *wfn="/tmp/ch2/myfile.txt";
	char buf[BLK]={' '};
	long long c=FILESIZE; 
	
	int wfd;

	fprintf(stderr,"creating huge file of size %dMB. Enter ctrl-C to abort. then run \"make clean\"\n",FILESIZE/(1024*1024));

	wfd=open(wfn,O_WRONLY|O_CREAT|O_TRUNC,0660);

	printf("wfd=%d\n",wfd);

	while (c-=BLK) {
		fprintf(stderr,".");
		write(wfd,buf,BLK);
		sleep(1);
	}
		fprintf(stderr,"\n");

	exit(0);
}

