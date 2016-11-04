// http://www.bruceblinn.com/linuxinfo/ByteOrder.html

#include <stdio.h>

int main() {
	
	int n=0;

	union {
		int i;
		char c[sizeof(int)];
	} foo;

	foo.i = 1;
	printf("%d .. %s Endian\n",foo.i, ((foo.c[0] == 1)? "Little" : "Big"));

	for (n=0;n<sizeof(int);n++)
		printf("foo.c[%d]=%d\n",n,foo.c[n]);

	return 0;
}
