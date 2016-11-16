// ch2_7.c

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv) {
 	int rfd, openflags;
	char *rfn="myfile.txt";

	if (argc < 2)  {
		fprintf(stderr,"Usage %s: <filename>\n",argv[0]);
		return;
	}
		
		argv++;

		rfn= *argv++;
		openflags = O_RDONLY;
		rfd=open(rfn, openflags,0660);
		printf("file \"%s\" open O_RDONLY fd=%d; flags=%#010x\n",rfn,rfd, openflags);
		// close(rfd);

		rfn= *argv++;
		openflags = O_WRONLY;
		rfd=open(rfn, openflags,0660);
		printf("file \"%s\" open O_WRONLY fd=%d; flags=%#010x\n",rfn,rfd, openflags);
		// close(rfd);

		rfn= *argv++;
		openflags = O_RDWR;
		rfd=open(rfn, openflags,0660);
		printf("file \"%s\" open O_RDWR fd=%d; flags=%#010x\n",rfn,rfd, openflags);
		// close(rfd);

		rfn= *argv++;
		openflags = O_CREAT;
		rfd=open(rfn, openflags,0660);
		printf("file \"%s\" open O_CREAT fd=%d; flags=%#010x\n",rfn,rfd, openflags);
		// close(rfd);

		rfn= *argv++;
		openflags = O_TRUNC;
		rfd=open(rfn, openflags,0660);
		printf("file \"%s\" open O_TRUNC fd=%d; flags=%#010x\n",rfn,rfd, openflags);
		// close(rfd);

		rfn= *argv++;
		openflags = O_APPEND;
		rfd=open(rfn, openflags);
		printf("file \"%s\" open O_APPEND fd=%d; flags=%#010x\n",rfn,rfd, openflags);
		// close(rfd);

		rfn= *argv++;
		openflags = O_WRONLY|O_TRUNC|O_CREAT|O_APPEND;
		rfd=open(rfn, openflags);
		printf("file \"%s\" open O_WRONLY|O_TRUNC|O_CREAT|O_APPEND fd=%d; flags=%#010x\n",rfn,rfd, openflags);
		// close(rfd);

	exit(0);

}
