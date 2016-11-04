#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp) {

	int i=0, ret;

	char *newargv[16];

	newargv[i++]="ls";
	newargv[i++]="-l";
	newargv[i++]=0;

	ret=execlp(newargv[0],newargv[0],newargv[1],(char *)0);

	fprintf(stderr,"Hello World!\n");  // Code not reached!!

	return 0;

}
