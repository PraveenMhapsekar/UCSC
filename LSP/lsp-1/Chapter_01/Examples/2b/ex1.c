#include <stdio.h>

int main() {
	
	printf("PID==%d\n",getpid());

	while (putchar(  getchar() ));

}
