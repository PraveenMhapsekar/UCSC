#include <stdio.h>

int main()
{
	fprintf(stderr,"My PID==%u\n",getpid());
	while(1);
}
