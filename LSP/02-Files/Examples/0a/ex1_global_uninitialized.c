/* #1. Global Uninitialized Array */
#include <stdio.h>

int myarray[50000];

int main(void) {
	int c;

	myarray[0]=1;
	fprintf(stderr,"PID==%d\n",getpid());
	c=getchar(); // to insert a pause for pmap analysis
	return 0;
}
