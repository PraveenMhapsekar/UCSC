// 2nd example .. negative test for mismatch case

#include <stdio.h>

int main(int argc, char **argv, char **envp) {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="Testing ls";
	newargv[i++]="-f";
	newargv[i++]=0;

	execve(newargv[0], newargv, newenvp);

	// code not reached ??
	fprintf(stderr,"Hello World! ...  Code not reached!!\n");

}
	
