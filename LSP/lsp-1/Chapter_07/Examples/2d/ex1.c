#include <stdio.h>
#include <string.h>

int main() {

	char *str="Hello World";
	char buf[20];

	int fd[2];
	int rc,rcrd=1,rcwr;

	fprintf(stderr,"MyPID==%d\n",getpid());

	// str[0]=0;

	if ((rc=pipe(fd))>-1) {
		rcwr=write(fd[1],str,strlen(str));
		while(rcrd)
			rcrd=read(fd[0],buf,sizeof(buf));
	}	

	if (rcrd>0)
		buf[rcrd]=0;

	printf("Got \"%s\".\n",buf);

	return 0;
}
