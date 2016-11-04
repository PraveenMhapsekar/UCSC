// initialize a variable without touching it
#include <stdio.h>

#define str "HELLO"

int main()
{
	char m[5];
	int c=50;

	printf("c==%d\n",c);
	sprintf(m,"%s",str);
	printf("c==%d (%x %c) \n",c,c,c);

	return 0;
}
