#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

	int i=0;
	pid_t pid;
	fprintf(stderr,"Hello World pid=%d!\n",(int) getpid() );
	pid=fork();

	fprintf(stderr,"Hello World pid=%d!\n",(int) getpid() );

	switch (pid) {
		case -1: 
			printf("fork failed .. %d!\n",(int) getpid() );
		  break;
		case 0:	
			printf("this is child %d .. with the passed-in pid=%d\n", getpid(), pid);
			for (i=0;i++<5;) {
				fprintf(stderr,"PID=%d,PPID=%d.\n", getpid(), getppid());
				sleep(2);
			}	
			break;
		default:
			sleep(5);
			printf("this is parent %d .. with the child pid %d\n", getpid(), pid);
	    exit(0);
			break;
	}

	return 0;
}
