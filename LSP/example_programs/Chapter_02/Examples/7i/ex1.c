#include <stdio.h>
#include <fcntl.h>


int main() {

	int c,rfd;

	char *rfn="myfile.txt";

	fprintf(stderr,"Enter a char:\n");

	c=getchar();
	fprintf(stderr,"You entered a '%c':\n",c);

	rfd=open(rfn,O_RDONLY);
	fprintf(stderr,"We got fd='%d' for file '%s':\n",rfd,rfn);

   // close(0);

   dup2(rfd,0);  // would duplicate 'rfd' into slot '0'. it closes '0' then does the dup. 

   close(rfd);
   while ((c=getchar()) != EOF) {
      putchar(c);
   }
   return 0;
}

