#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

int main() {

	char *rfn="myfile.txt";
	int c;

	fprintf(stderr,"Enter a char:\n");
	c=getchar();
	fprintf(stderr,"You entered a '%c':\n",c);

	__fpurge(stdin);

	close(0);

	
	fprintf(stderr,"fd associated with stdin is '%d'.\n",fileno(stdin));

	open(rfn,O_RDONLY);

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	return 0;
}
