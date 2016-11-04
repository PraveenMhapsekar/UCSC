#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv, char **envp) {

	int i=0, rc=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="ls";
	newargv[i++]="-l";
	newargv[i++]=0;

	// rc=execve(newargv[0], newargv, newenvp);
	rc=execvp(newargv[0], newargv, envp);

	// code never reached!!
	printf("Hello World! RC=%d! Error is %d (%s)\n",
		rc,errno, strerror(errno));
}
