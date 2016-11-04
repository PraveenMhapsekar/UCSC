// to demo a filesystem full condition - for inode blocks
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>

// #define NUMFILES 10000000
#define NUMFILES 4100

int main() {

	int i=0,fd=0;
	char *fn="/tmp/ch2/ch2";
	char *wfn=malloc(50);
	
	for (i=0;i++<NUMFILES;) {
		sprintf(wfn,"%s_%5.5d",fn,i);

		fd=open(wfn,O_WRONLY|O_CREAT|O_TRUNC,0660);
	  close(fd);
	}

	free(wfn);

	return;
}	
