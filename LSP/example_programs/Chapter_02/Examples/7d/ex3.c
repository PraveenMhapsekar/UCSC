#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

int main() {

	FILE *wfp;
	char *wfn="myfile.txt";
	int c=0;

	fprintf(stderr,"sizeof(FILE)=%d:\n", sizeof(FILE));
	
	printf("Hello world!\n");

	close(1);

	wfp=fopen(wfn,"w");

	printf("%d. Hello world!\n",c++);
	printf("%d. Hello world!\n",c++);
	printf("%d. Hello world!\n",c++);
	printf("%d. Hello world!\n",c++);

	fclose(wfp);

	printf("%d. Hello world!\n",c++);
	printf("%d. Hello world!\n",c++);
	printf("%d. Hello world!\n",c++);
	printf("%d. Hello world!\n",c++);

	return 0;
}
