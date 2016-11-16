#include <stdio.h>
#include <string.h>

#define BUFSZ 6553600
int main() {

	char buf[BUFSZ];

	int fd[2];
	int rc,rcrd=0,rcwr,pid,i=0;

	if ((rc=pipe(fd))>-1) {

		switch (pid=fork()) {
			case -1:
				fprintf(stderr,"Fork failed.\n");
				return 0;
				break;	
			case 0:
				sleep(10);
				close(fd[1]);	// child closes write fd. child is listener.
				do {
					rcrd=read(fd[0],buf,sizeof(buf));
					fprintf(stderr,"child reads .. %d \n",rcrd);
			  } while (rcrd);
				if (rcrd>0) buf[rcrd]=0;
				fprintf(stderr,"Got \"%s\".\n",buf);
				close(fd[0]);
				break;
			default:
				close(fd[0]);	// parent closes read fd. parent is talker.
				while (i++<BUFSZ) buf[i]='a';
				write(fd[1],buf,strlen(buf));
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
