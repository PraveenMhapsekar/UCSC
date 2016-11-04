// ch2_1.c

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	int rfd;

	int i=0;

		rfd=open(rfn, O_RDONLY);
		printf("%d. Got fd=%d\n",i, rfd);
		close(rfd);

	return 0;
}
