// mismatch between newargv[0] & first argument to execve()

#include <stdio.h>

int main(int argc, char **argv, char **envp) {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="/bin/ls";
	newargv[i++]="-f";
	newargv[i++]=0;

	execve(newargv[0], newargv, newenvp);

	fprintf(stderr,"Hello World!\n");  // Code not reached!!

}
	
