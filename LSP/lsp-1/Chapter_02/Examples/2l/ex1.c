// ch2_5.c

#include <stdio.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	int rfd;
	rfd=open(rfn, O_RDONLY);

	close(rfd);
	close(rfd); /* .. multiple close() on same fd  is **mostly** ok. */
	close(rfd); /* .. multiple close() on same fd  is **mostly** ok. */
	
	return 0;
}
