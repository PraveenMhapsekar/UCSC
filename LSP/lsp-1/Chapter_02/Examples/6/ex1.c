#include <stdio.h>

int main() {

	int rfd;

	FILE *rfp;

	char *rfn="myfile.txt";

	if ((rfp=fopen(rfn, "r"))==(FILE *) NULL) {
		fprintf(stderr,"File \'%s\' not found!\n", rfn);
		return;
	}

	printf("'%s' is associated with fd => %d\n",
		rfn, fileno(rfp));

	printf("stdin fd => %d\n",fileno(stdin));
	printf("stdout fd => %d\n",fileno(stdout));
	printf("stderr fd => %d\n",fileno(stderr));

	fclose(rfp);
}
