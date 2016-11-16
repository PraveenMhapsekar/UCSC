#include <sys/ci/cilock.h>
#include <sys/ci/cimpdata.h>
#include <sys/ci/ciioctl.h>
#include <fcntl.h>
   
int main() {
	int fd; int num_CPUs;

	if ( (fd = open("/dev/at1", O_RDONLY)) < 0 ) 
    { perror("unable to open /dev/at1"); exit(1); }

	if ( ioctl(fd, ACPU_GETNUM, &num_CPUs) < 0 ) 
		{ perror("ACPU_GETNUM"); exit(1); } 

	printf("Total number of CPUs: %d\n", num_CPUs + 1); 
}
