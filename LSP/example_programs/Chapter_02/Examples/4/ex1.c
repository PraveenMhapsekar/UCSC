#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

int main() {

	char *rfn="myfile.txt";
	int rfd=0;
	int n=-1;
	char *buf=malloc(128);


	rfd=open(rfn,O_RDONLY);
	
	sprintf(buf,"The name of this file is '%s'\n.",rfn);
	while (n)
		n=read(rfd,buf,strlen(buf));

	printf("File has %d chars at EOF.\n",n);

	close(rfd);

	return 0;
}
	

	
