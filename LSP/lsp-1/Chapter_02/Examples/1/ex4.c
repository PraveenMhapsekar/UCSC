#include <stdio.h>

int main() {

	int c;

	c=getchar();

	printf("STDOUT: You entered a \"%c\".\n",c);
	fprintf(stderr,"PID=%d. STDERR: You entered a \"%c\".\n",getpid(),c);
	
  __fpurge(stdin);
	c=getchar();
	printf("STDOUT: You now entered a \"%c\".\n",c);
	fprintf(stderr,"PID=%d. STDERR: You now entered a \"%c\".\n",getpid(),c);

	return 0;
}
