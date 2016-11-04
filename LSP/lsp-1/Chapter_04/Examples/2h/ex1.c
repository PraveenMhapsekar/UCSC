#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER 18

main()
{
	unsigned int d=1,i=1;

	for (i=1;i<=NUMBER;i++) d*=i;

	printf("i=%d .. d=%u\n", i-1,d);

	return 0;
}
