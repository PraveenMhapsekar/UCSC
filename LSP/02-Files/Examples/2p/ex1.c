#define MAXBUFSZ 200

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char *wfn= "myfile.out";

int main() {
	int rfd, wfd;  			// read and write fd's
	int nr,nw;				// number read and written
	char *buf=malloc(MAXBUFSZ);
	wfd=open(wfn, O_WRONLY|O_APPEND|O_CREAT|O_TRUNC,0666);

	buf[0]=0;
	
	while (fgets(buf,MAXBUFSZ,stdin)) {
		nw=write(wfd,buf,strlen(buf));
	
		buf[strlen(buf)]=0;	// strip out '\n'
		nr=strlen(buf);
		fprintf(stderr,"Bytes Read='%d'; Bytes Written='%d'.\n",nr,nw);
		buf[0]=0;	
	}

	close(wfd);
}
