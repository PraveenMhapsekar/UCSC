#include <stdio.h>
#include <fcntl.h>

int main()
{

	int c;
  int fd;

  c=getchar();
  __fpurge(stdin); // __fpurge() here. 

  fprintf(stderr,"Hello .. you entered \"%c\".\n", c);
  
  close(0);
  // __fpurge(stdin); // __fpurge() here. 

  fd=open("myfile.txt", O_RDONLY);
  fprintf(stderr,"Got fd==%d.\n", fd);

  while ((c=getchar())!=EOF)	
		putchar(c);

  fprintf(stderr,"EOF.\n", c);
}
