#include <stdio.h>
#include "ex1.h"

void myprintf(char *arg, char *arg2) {
	printf("In Dir \"%s\": Hello %s .. Testing %d from PID %d\n", arg2, arg, TESTNUM, getpid());
}


int main() {
	
	char *str;
	char *str2;

	str=(char *)getenv("PARM1");
	str2=(char *)getenv("PARM2");

	if (str)
		myprintf(str,str2);

	return 0;
}
