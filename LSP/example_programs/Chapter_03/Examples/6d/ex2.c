#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {

	pid_t mypid;
	fprintf(stderr,"Hello World pid=%d!\n",(int) getpid() );

	mypid=fork();

	if (mypid==-1)  {
		fprintf(stderr,"fork failed=%d (%s)!",
			errno,strerror(errno));
		return -1;
	}
		
	if (mypid > 0) 
		printf("\nthis is parent %d .. with the child pid %d\n", 
			getpid(), mypid);
	else	
		printf("\nthis is child %d .. with the passed-in pid=%d\n", 
			getpid(), mypid);


	return 0;
}
