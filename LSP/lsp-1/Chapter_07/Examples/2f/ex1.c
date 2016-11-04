#include <stdio.h>
#include <string.h>

int main() {

	char *str="Hello World";
	char buf[50];

	int fd[2];
	int rc,rcrd,rcwr,pid;

	if ((rc=pipe(fd))>-1) {

		switch (pid=fork()) {
			case -1:
				fprintf(stderr,"Fork failed.\n");
				return 0;
				break;	
			case 0:
				sleep(1);
				close(fd[1]);	// child closes write fd. child is listener.
			  fprintf(stderr,"Sleeping 5 ... ");
				sleep(5);
				close(fd[0]); // close [0]
				break;
			default:
				// what happens when an 'incorrect read end' is not closed ?
				close(fd[0]);  // also, close[0]
        sprintf(buf,"%s .. from PID '%d'",str,getpid());
 				while (rcwr)
     			rcwr=write(fd[1],buf,strlen(buf));
				break;	
		}	
	}	

	return 0;
}
