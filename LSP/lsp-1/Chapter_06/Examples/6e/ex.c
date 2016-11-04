#include <stdio.h>
#include "ex.h"

void myprintf(void);

int main() {
	int c;

	myprintf();

	fprintf(stderr,"Enter a char:(PID==%d)",getpid());
	c=getchar();
	return 0;
}
