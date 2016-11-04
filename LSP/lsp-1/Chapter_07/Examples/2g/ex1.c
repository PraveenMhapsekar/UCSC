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
				// close(fd[1]);	// child closes write fd. child is listener.

				rcrd=-1;
			  system("ps -f");
				while(rcrd)
					rcrd=read(fd[0],buf,sizeof(buf));
				if (rcrd>0) buf[rcrd]=0;
				fprintf(stderr,"Got \"%s\".\n",buf);
				// close(fd[0]);
				break;
			default:
				close(fd[0]);	// parent closes read fd.
				close(fd[1]);	// parent closes write fd.
				fprintf(stderr,"Parent is sleeping.\n");
				sleep(3);
				// close(fd[1]);	// parent closes write fd.
				break;	
		}	
	}	

	return 0;
}
