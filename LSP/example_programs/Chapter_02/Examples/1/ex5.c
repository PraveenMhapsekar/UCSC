#include <stdio.h>
#include <fcntl.h>

int main()
{
	char *rfn="ex5.c";
	int c;

	c=getchar();
  fprintf(stderr,"You entered a '%c'.\n",c);

	close(0);
	open(rfn,O_RDONLY);

  while ((c=getchar())!=EOF)
		putchar(c);
}
