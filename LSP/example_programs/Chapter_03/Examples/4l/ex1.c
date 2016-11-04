#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv, char **envp) {

	int i=0;
  int rc=0;

	char *newargv[16];
	char *newenvp[16];

	newenvp[0]=0;

	newargv[i++]="./ls";  // Non-existent executable.
	newargv[i++]="-f";
	newargv[i++]=0;

	rc=execve(newargv[0], newargv, envp);
/*
  if (rc < 0) 
  {
     printf(" Bailing out here ... \n");
     return 0;
  }
*/
	// code never reached!!
	printf("Hello World ... rc=(%d)%s\n", rc, strerror(errno));

	return 0;

}
	
