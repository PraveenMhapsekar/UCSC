/* #3. Stack Uninitialized Array */
#include <stdio.h>

void fn1(void); 

int main(void) {
	int c;

	fprintf(stderr,"PID==%d\n",getpid());
	c=getchar(); // to insert a pause for pmap analysis
	fn1();
	fprintf(stderr,"Again PID==%d\n",getpid());
	c=getchar(); // to insert a pause for pmap analysis
	return 0;
}


void fn1(void) 
{
	int myarray[50000];
	myarray[0]=1;
	fprintf(stderr,"In fn1\n");
}


