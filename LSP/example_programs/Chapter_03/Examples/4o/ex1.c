#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp) {

	int i=0, ret;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="/bin/ls";
	newargv[i++]="-l";
	newargv[i++]=0;

	ret=execle(newargv[0],newargv[0],newargv[1],(char *)0,newenvp);

	fprintf(stderr,"Hello World!\n");  // Code not reached!!

}
	
