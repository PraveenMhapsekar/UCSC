// sourced from http://www.linuxforums.org/forum/kernel/119061-how-call-ioctl-function.html


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/cdrom.h>


int main (int argc, char **argv)
{
	
// char *dev="/dev/cdrom";
// char *dev="/dev/sr0";

	char *dev=argv[1];
	int fd, rc;

 // Open fd to the dev
	if ((fd = open (dev, O_RDONLY|O_NONBLOCK))<0) {
		perror("Open");
		exit(0);
	}

// Eject CD-ROM; CDROMEJECT is device_ioctl.. 
	if ((rc=ioctl(fd, CDROMEJECT,0x0))<0)  {
		perror("IOCTL");
 		return 0;
  }

	close (fd); /* Close the file descriptor. */

	return 0;
}

