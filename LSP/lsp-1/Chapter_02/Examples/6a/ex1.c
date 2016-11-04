#include <stdio.h>
#include <fcntl.h>

int main() {

	int rfd;

	FILE *rfp;

	char *rfn="myfile.txt";

	if ((rfd=open(rfn, O_RDONLY))<0) {
		fprintf(stderr,"File \'%s\' not found!\n", rfn);
		return;
	}

	rfp=fdopen(rfd,"r");

	printf("fd => %d\nsizeof(FILE)==%d\n",fileno(rfp),sizeof(FILE));

	fclose(rfp);
}
