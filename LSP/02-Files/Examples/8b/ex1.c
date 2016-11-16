// sourced from http://www.linuxjournal.com/article/6908

#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

int main()
{
  int fd, status;

   if ((fd = open("/dev/ttyS0", O_RDONLY))<0) {
			fprintf(stderr,"TTY device not found\n");
			return 0;
	 }

   if (ioctl(fd, TIOCMGET, &status) == -1)
      printf("TIOCMGET failed: %s\n", strerror(errno));
   else {
      if (status & TIOCM_DTR)
         puts("TIOCM_DTR is not set");
      else
         puts("TIOCM_DTR is set");
   }
   close(fd);

	 return 0;
}
