#include <stdio.h>
#include "ex1.h"

void myprintf(char *arg) {
	printf("Hello %s .. Testing %d from PID %d\n", arg, TESTNUM, getpid());
}


int main() {
	
	char *str;

	str=(char *)getenv("PARM1");

	if (str)
		myprintf(str);

	return 0;
}
