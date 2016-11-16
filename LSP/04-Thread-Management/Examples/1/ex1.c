#include <stdio.h>
#include <unistd.h>

int main() {
	int pid;

	printf("Before fork .. Hello World (PID=%d)\n",getpid());

	pid=fork();

	if (pid)
		return 0;			// parent return immediately

	sleep(4);
	printf("CHILD: After fork .. Hello World = %d\n", getpid());

	return 0;
}
	
