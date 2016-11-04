// to demo a filesystem full condition for datablocks
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

#define NUMFILES 10
#define BLKSIZE 2000000

int main() {

	int i=0,fd=0;
	char *fn="/tmp/ch2/ch2";
	char *wfn=malloc(50);
	char *buf=malloc(BLKSIZE);
	
	for (i=0;i++<NUMFILES;) {
		sprintf(wfn,"%s_%4.4d",fn,i);

		fd=open(wfn,O_WRONLY|O_CREAT,0660);
	  write(fd,wfn,strlen(wfn));
	  // lseek(fd,BLKSIZE,SEEK_END);
	  write(fd,buf,BLKSIZE);
	  close(fd);
	}

	free(wfn);
	free(buf);

	return;
}	
