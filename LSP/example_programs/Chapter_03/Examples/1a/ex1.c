#include <stdio.h>
#include <malloc.h>

char *s1="%s\n";
char *s2="Hello World!";

int main() {
	int c;

	int *iptr;
	int *iptr2;
	int iptr3[50000];

	// iptr=(int *)malloc(50000*sizeof(int));
	// iptr2=(int *)malloc(75000*sizeof(int));

	// iptr[10000]=0;
	// iptr2[10000]=0;
	
	printf(s1,s2);

	fprintf(stderr,"Waiting ... for a char (PID=%d).\n",getpid());
	c=getchar();
	
	// free(iptr);
	// free(iptr2);
	return (0);
}
