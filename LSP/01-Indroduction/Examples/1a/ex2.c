#include <stdio.h>

#define HELLO "hello";

int main() {

	int c;
	c=getchar();

	printf("%s ... You entered %c.",HELLO, c);

	return 0;
}
