#include <stdio.h>

int main() {

	int c;

	printf("Enter a char:\n");
	c=getchar();

	printf("you entered '%c'.\n",c);

	ungetc(c+1,stdin);
	ungetc(c+2,stdin);
	ungetc(c+3,stdin);
	c=getchar();
	printf("changed value '%c'.\n",c);
	c=getchar();
	printf("changed value '%c'.\n",c);
	c=getchar();
	printf("changed value '%c'.\n",c);
	c=getchar();
	printf("you entered '%c'.\n",c);
	c=getchar();
	printf("you entered '%c'.\n",c);
	c=getchar();
	printf("you entered '%c'.\n",c);
}
