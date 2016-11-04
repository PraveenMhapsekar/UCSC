#include <stdio.h>

int main() {

	int i=0;

	char *newargv[16];
	// char *newenvp[16];

	// newenvp[0]=0;

	newargv[i++]="/bin/ls";
	newargv[i++]="-af";
	newargv[i++]=0;

	execv(newargv[0], newargv);

	// code never reached!!
	printf("Hello World\n");

	return 0;
}
	
