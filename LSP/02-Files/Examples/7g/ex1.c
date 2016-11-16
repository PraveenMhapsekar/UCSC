#include <stdio.h>
#include <fcntl.h>


int main() {

	int c,rfd;

	char *rfn="myfile.txt";

	fprintf(stderr,"Enter a char:\n");

	c=getchar();
	fprintf(stderr,"You entered a '%c':\n",c);

	rfd=open(rfn,O_RDONLY); // should be == 3.
	fprintf(stderr,"We got fd='%d' for file '%s':\n",rfd,rfn);

   close(0);

   dup(rfd);  // create a duplicate fd of the given fd; using the lowest available fd#

   close(rfd);	// do we care about fd==3 ? ..
   while ((c=getchar()) != EOF) {
      putchar(c);
   }
   return 0;
}

