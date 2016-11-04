#include <stdio.h>

int main() {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="ls";
	newargv[i++]="-f";
	newargv[i++]=0;

	execvp(newargv[0], newargv);

	// code never reached!!
	printf("Hello World\n");

	return 0;
}
	
