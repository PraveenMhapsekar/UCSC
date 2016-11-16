#include <stdio.h>
#include <malloc.h>
#include <string.h>


void fn(char *);

int main() {

	char *c=malloc(50);     // local variables go onto stack.
													// malloc goes on heap
	
	strcpy(c,"Hello World");	

	fn(c);

	free(c);

	return;

}

void fn(char *i) // function arguments .. go onto stack
{  
	printf("Value passed to fn is \"%s\"\n", i);
}
	
  
