#include <stdio.h>
#include <stdlib.h>

int main() 
{
	int a=5;
	int b=5;

  int rc=0;

  rc=a++ + ++b;
	printf ("Hello! a=%d, b=%d, rc=%d\n",a,b,rc);

	exit(0);
}
