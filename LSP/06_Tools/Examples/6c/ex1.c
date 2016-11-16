#include <stdio.h>
#include "ex.h"

void myprintf(char *msg);
void myprintf2(void);

int main() {

	int c;

	// myprintf("Hello World");
	myprintf2();

	fprintf(stderr,"Enter a char:");
	c=getchar();

	return 0;
}
