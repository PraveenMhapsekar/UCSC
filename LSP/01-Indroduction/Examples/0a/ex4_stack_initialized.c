/* #4. Stack Initialized Array */
#include <stdio.h>

int main(void) {
	int myarray[50000]={100};
	int c;

	myarray[0]=1;
	fprintf(stderr,"PID==%d\n",getpid());
	c=getchar(); // to insert a pause for pmap analysis
	return 0;
}
