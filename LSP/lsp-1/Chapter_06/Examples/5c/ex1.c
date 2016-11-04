#include <stdio.h>
#include "ex1.h"

void myprintf(char *arg) {
	printf("Hello %s .. Testing %d\n", arg, TESTNUM);
}


int main() {
	
	char *str;

	str=(char *)getenv("PARM1");

	if (str)
		myprintf(str);

	return 0;
}
