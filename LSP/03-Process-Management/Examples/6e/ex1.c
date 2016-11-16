#include <stdio.h>
#include <unistd.h>

int main() {

	pid_t pid;
	fprintf(stderr,"Hello World pid=%d!",(int) getpid() );


	pid=fork();

	if (pid >= 0) {
		if (pid > 0) 
			printf("this is parent %d .. with the child pid %d\n", getpid(), pid);
		else	
			printf("this is child %d .. with the passed-in pid=%d\n", getpid(), pid);
	}
	else 
		printf("fork failed .. %d!\n",(int) getpid() );

	return 0;
}
