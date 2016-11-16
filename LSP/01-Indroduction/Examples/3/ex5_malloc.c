#include <stdio.h>
#include <malloc.h>
 
int main(void) {
	int *myarray=(int *) malloc(50000 * sizeof(int));
	int c;

	myarray[0]=1;
	fprintf(stderr,"PID==%d\n",getpid());
	c=getchar();
	free(myarray);
	return 0;

}
