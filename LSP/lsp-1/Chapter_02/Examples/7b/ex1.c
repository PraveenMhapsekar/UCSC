#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int c;

	fprintf(stderr,"Enter a char:\n");
	c=getchar();
	fprintf(stderr,"You entered a '%c':\n",c);

	// ungetc(c,stdin);
	ungetc(c+7,stdin);

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	exit (0);

}
