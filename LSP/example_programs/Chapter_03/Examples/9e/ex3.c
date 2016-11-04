#include <stdio.h>

int main() {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[0]="/bin/cat";
	newargv[1]="./ex3.sh";
	newargv[2]=0;

	execve(newargv[0], newargv, newenvp);

}
	
