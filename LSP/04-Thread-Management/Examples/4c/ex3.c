#include <stdio.h>

int main()
{
	fprintf(stderr,"PID==%d",getpid());
	while(1);
}
