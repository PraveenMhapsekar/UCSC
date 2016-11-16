// mismatch between newargv[0] & first argument to execve()

#include <stdio.h>

int main(int argc, char **argv, char **envp) {

	int i=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="virus";
	newargv[i++]="-f";
	newargv[i++]=0;

  system("ps -f");
  fprintf(stderr,"system(\"ps -f\") finished.\n");

	execve("/bin/ps", newargv, newenvp);

	fprintf(stderr,"Hello World!\n");  // Code not reached!!

}
	
