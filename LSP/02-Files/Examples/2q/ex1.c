#include <stdio.h>
#include <fcntl.h>

int main()
{

	int c;
  int fd;

  c=getchar();

  fprintf(stderr,"Hello .. you entered \"%c\".\n", c);
  
  close(0);

  fd=open("myfile.txt", O_RDONLY);
  fprintf(stderr,"Got fd==%d.\n", fd);

  while ((c=getchar())!=EOF)	
		putchar(c);

  fprintf(stderr,"EOF.\n", c);
}
