#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

#include <errno.h>

int main() {

	char *wfn="myfile2.txt";
	char *str="Hello! This is myfile2.txt";
	int c,fd=0;


	fd=open(wfn,O_WRONLY|O_CREAT|O_TRUNC);

	fprintf(stderr,"=> Got fd='%d'\n",fd);

	if (fd<0) {
		fprintf(stderr,"Error! '%d' => \"%s\"\n",errno, strerror(errno));
		return;
	}

	fprintf(stderr,"=> Writing \"%s\" to file \"%s\"!\n", str, wfn);

	c=write(fd,str,strlen(str)); 

	fprintf(stderr,"=> Wrote '%d' to above file.\n", c);

	close(fd);
	
	system("ls -l myfile2.txt");
	
	return 0;
}
