#include <stdio.h>

int main(int argc, char **argv, char **envp) {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="/bin/ls";
	newargv[i++]=0;

	// execve("/bin/ls", newargv, newenvp);
	execve("/bin/ls", newargv, envp);

	fprintf(stderr,"Hello World!\n");  // Code not reached!!

}
	
