#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // execlp
#include <sys/types.h>

int main() {
	int pid;

	if (pid=fork()) {
  	/* parent code */
  	exit(0);
	} else {
  	/* child code */
		sleep(5);
  	execlp( "ls", "ls", "-l", (char *)0);


		// code never reached!
  	printf("Should never get here...\n");
  	exit (-1);
	}
}
