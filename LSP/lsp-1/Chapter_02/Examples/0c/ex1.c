#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


char *c1="Hello World";

int main() {
	char c;

	printf("%s\n",c1);

	c1=malloc(25*1024*1024);

	strcpy(c1,"Hello Universe\n");

	printf("PID=%d .. %s\n",getpid(), c1);

  sleep (90);

	free(c1);

	fprintf(stderr,"enter to continue");

	c=getchar();

	exit(0);
}
