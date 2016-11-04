#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv, char **envp) {

	int i=0, rc=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="ls"; //
	newargv[i++]="-l";
	newargv[i++]=0;

	printf("This is currently executing \"%s\" with PID=%d\n", 
		argv[0],getpid());

	rc=execvp(newargv[0], newargv);

	// code never reached!!
	printf("Hello World! RC=%d! Error is %d (%s)\n",
		rc,errno, strerror(errno));
	
	return 0;
}
	
