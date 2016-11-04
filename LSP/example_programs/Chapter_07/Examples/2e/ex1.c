#include <stdio.h>
#include <string.h>

int main() {

	char *str="Hello World";
	char buf[50];

	int fd[2];
	int rc,rcrd=0,rcwr,pid;

	if ((rc=pipe(fd))>-1) {

		switch (pid=fork()) {
			case -1:
				fprintf(stderr,"Fork failed.\n");
				return 0;
				break;	
			case 0:
				// introduce a 1sec delay.
				sleep(1);
				// Write end closed here
				close(fd[1]);	// child closes write fd. child is listener.
				fprintf(stderr,"Child PID==%d.\n", getpid());
				do {
					rcrd=read(fd[0],buf,sizeof(buf));
					fprintf(stderr,"child reads .. %d \n",rcrd);
			  } while (rcrd);
				if (rcrd>0) buf[rcrd]=0;
				fprintf(stderr,"Got \"%s\".\n",buf);
				close(fd[0]);
				break;
			default:
				fprintf(stderr,"Parent PID==%d.\n", getpid());
				// Read end closed here
				close(fd[0]);	// parent closes read fd. parent is talker.
				write(fd[1],str,strlen(str));
				// Write end closed here
				close(fd[1]);
			  fprintf(stderr,"All write ends are closed. Sleeping 5 ... ");
		    system("date");
		    system("ps -f");
        sleep(8);
		    system("date");
		    system("ps -f");
				break;	
		}	
	}	

	return 0;
}
