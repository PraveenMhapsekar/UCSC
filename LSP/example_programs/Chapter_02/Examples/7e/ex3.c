#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

int main() {

	FILE *rfp;
	char *rfn="myfile.txt";
	int c;

	fprintf(stderr,"Enter a char:\n");
	c=getchar();
	fprintf(stderr,"You entered a '%c':\n",c);

	close(0);

	ungetc(++c,stdin);

	rfp=fopen(rfn,"r");

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	return 0;
}
