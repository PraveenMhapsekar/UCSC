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
				close(fd[0]);	// child closes read fd. child is talker.
				sprintf(buf,"%s .. from PID '%d'",str,getpid());
				rcwr=write(fd[1],buf,strlen(buf));	
				sleep(1);
				system("ps -f");
				break;	
			default:
				close(fd[1]);	// parent closes write fd. parent is listener.
				rcrd=read(fd[0],buf,sizeof(buf));
				if (rcrd>0) buf[rcrd]=0;
				fprintf(stderr,"In Parent (PID==%d) => Got \"%s\".\n",getpid(),buf);
				break;
		}	
	}	

	return 0;
}
