#include <stdio.h>
#include <unistd.h>

int main() {

	int i=0;

	pid_t pid;
	fprintf(stderr,"Hello World pid=%d!",(int) getpid() );


	pid=fork();
	
	switch (pid) {
		case -1: 
			printf("fork failed .. %d!\n",(int) getpid() );
		  break;
		case 0:	
			printf("this is child %d .. with the passed-in pid=%d\n", 
						getpid(), pid);
			sleep(3);
			for (i=0;i++<5;) {
				printf("%d. Hello!\n",i);
			  sleep(3);
			}
			break;
		default:
			printf("this is parent %d .. with the child pid %d\n", getpid(), pid);
			return 0;
			break;
	}

	return 0;
}
