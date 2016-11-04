#include <stdio.h>

int main()
{	
	int c;

	fprintf(stderr,"PID==%d\n",getpid());

	while ((c=getchar())!=EOF)
		putchar(c);

	sleep(180);

	return 0;
}
