#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	fprintf(stderr,"PID==%d\n",getpid());
	while (1);
}

