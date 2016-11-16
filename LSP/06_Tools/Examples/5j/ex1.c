#include <stdio.h>
#include "ex1.h"

void myprintf(char *arg) {
	system ("ps -f");
	printf("Hello %s .. Testing %d from PID=%d PPID=%d\n", arg, TESTNUM, getpid(),getppid());
}

int main() {
	
	char *str;

	str=(char *)getenv("PARM1");

	if (str)
		myprintf(str);

}
