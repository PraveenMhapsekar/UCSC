#include <stdio.h>
#include <unistd.h>

int main() {

	pid_t pidt;
	fprintf(stderr,"Hello World pid=%d!",(int) getpid() );


	pidt=fork();

	switch (pidt) {
		case -1: 
			printf("fork failed .. %d!\n",(int) getpid() );
		  break;
		case 0:	
			printf("\nthis is child %d .. with the passed-in pid=%d\n", 
				getpid(), pidt);
			break;
		default:
			printf("\nthis is parent %d .. with the child pid %d\n", 
				getpid(), pidt);
			break;
	}

	return 0;
}
