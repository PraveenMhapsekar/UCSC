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
			  fprintf(stderr,"Child PID==%d\n",getpid());
				close(fd[0]);	// child closes read fd. child is the talker.

				rcwr=-1;
				// while(rcwr)
				// rcwr=write(fd[1],str,sizeof(str));
				close(fd[1]);	// child closes write fd.
				break;
			default:
			  fprintf(stderr,"Parent PID==%d\n",getpid());
				// close(fd[1]);	// parent closes write fd. child is the listener.
				fprintf(stderr,"Parent is sleeping.\n");
				system("ps -f");
				close(fd[0]);	// parent closes read fd.  
				sleep(5);
				break;	
		}	
	}	

	return 0;
}
