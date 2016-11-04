// generates error since it uses execve and the full path is *not* provided
#include <stdio.h>

int main() {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="ls";   // No Full Path!!!
	newargv[i++]="-f";
	newargv[i++]=0;

	execve(newargv[0], newargv, newenvp);

	// code never reached!!
	printf("Hello World\n");

	return 0;
}
	
