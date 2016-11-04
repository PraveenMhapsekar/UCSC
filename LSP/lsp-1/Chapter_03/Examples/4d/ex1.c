// print 'ps' output

#include <stdio.h>

int main(int argc, char **argv, char **envp) {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="/bin/ps";
	newargv[i++]="-f";
	newargv[i++]=0;

	system("ps -f");
  fprintf(stderr,"system(\"ps -f\") finished.\n");
	sleep(1);

	execve("/bin/ps", newargv, newenvp);

	fprintf(stderr,"Hello World!\n");  // Code not reached!!

}
	
