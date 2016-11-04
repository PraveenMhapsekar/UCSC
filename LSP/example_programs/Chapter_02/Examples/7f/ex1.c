// ch2_10a.c
#define 	_POSIX_SOURCE 1

#include <stdio.h>
#include <stdio_ext.h>   // __fpurge()
#include <stdlib.h>
#include <fcntl.h>

/*
The function fflush() forces a write of all user-space buffered data for the given output or update stream via the stream's underlying write function.

The function fpurge() clears the buffers of the given stream. For output streams this discards any unwritten output. For input streams this discards any input read from the underlying object but not yet obtained via getc(3); this includes any text pushed back via ungetc(). See also fflush(3).

The function __fpurge() does precisely the same, but without returning a value. 
*/

int main() {
	 char *rfn="myfile.txt";

	 char c;
	
	 int rfd;

	 printf("Waiting for input\n");

   c=getchar();

		fprintf(stderr,"You entered a '%c':\n",c);

	 // fpurge(stdin); // available in some C libs
	 __fpurge(stdin); // available in some C libs
	 close(0);

   rfd=open(rfn,O_RDONLY);

	 printf("rfd=%d\n",rfd);

   while ((c=getchar()) != EOF) {
		putchar(c);
	 }
	exit(0);
}
 
