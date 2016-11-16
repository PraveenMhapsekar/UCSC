#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

int main() {

	FILE *rfp;
	char *rfn="myfile.txt";
	int c;

	fprintf(stderr,"sizeof(FILE)=%d:\n", sizeof(FILE));
	fprintf(stderr,"Enter a char:\n");
	c=getchar();
	fprintf(stderr,"You entered a '%c':\n",c);

	close(0);

	rfp=fopen(rfn,"r");

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	return 0;
}
