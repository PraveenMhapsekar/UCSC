#include <stdio.h>
#include <string.h>

// Happy Path
// #define BUFSZ 5			

// Happy Path
// #define BUFSZ 1024

// Happy Path
// #define BUFSZ 4099

// about 6MB
#define BUFSZ 6553600

int main() {

	char *str="Hello World";

	char buf2[BUFSZ];

	int fd[2];
	int rc,rcrd,rcwr=1;
	int i=0;

	if ((rc=pipe(fd))>-1) {

		// fill the buffer to BUFSZ
		while (i<BUFSZ) buf2[i++]='a';

	  buf2[i]=0;
		fprintf(stderr,"MyPID==%d\n",getpid());	
		rcwr=write(fd[1],buf2,strlen(buf2));
		
		rcrd=read(fd[0],buf2,sizeof(buf2));
	}	

	if (rcrd>0)
		buf2[rcrd]=0;

	printf("Got \"%s\".\n",buf2);

	return 0;
}
