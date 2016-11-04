// ch2_1.c

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

char *wfn= "myfile.txt";

int main() {
	int wfd;

	int i=0;

	wfd=open(wfn,O_TRUNC,0666);
	printf("%d. Got fd=%d\n",i, wfd);
	close(wfd);

	return 0;
}
