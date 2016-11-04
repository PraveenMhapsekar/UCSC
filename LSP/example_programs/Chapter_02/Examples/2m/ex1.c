// ch2_6.c

#include <stdio.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	int rfd1, rfd2;
	rfd1=open(rfn, O_RDONLY);

	printf("Got fd=%d!\n",rfd1);

	rfd2=open(rfn, O_RDONLY);
	printf("Got fd=%d!\n",rfd2);

	close(rfd1);
	close(rfd2); /* .. different descriptor .. ok. */
}
