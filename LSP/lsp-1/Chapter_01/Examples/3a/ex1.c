#include <stdio.h>

void fn(int);

int main() {

	int i;     // local variables go onto stack.
	i=5;

	fn(i);

	printf("Awaiting Input...");
	i=getchar();

	return 0;

}

void fn(int i) // function arguments .. go onto stack
{  
  int c=0;
	printf("PID==%d\n", getpid());
	printf("Value passed to fn is %d\n", i);
	
	c=getchar();
}
	
  
