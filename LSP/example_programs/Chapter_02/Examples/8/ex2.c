#include <stdio.h>
#include <fcntl.h>

int main() {

	int c;
	int flags;
	int fd=0;

	flags=fcntl(fd,F_GETFL, 0);

  flags |= O_NONBLOCK;
  c=fcntl(fd, F_SETFL, flags);

	while ((c=getchar())!=EOF) 
		putchar(c);

  flags &= ~O_NONBLOCK;
  c=fcntl(fd, F_SETFL, flags);

	return 0;
}
