#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

int main() {
	int c;

	fprintf(stderr,"Enter a char:\n");
	c=getchar();
	fprintf(stderr,"You entered a '%c':\n",c);

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

}
