// ch2_1.c

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

char *wfn= "myfile.txt";

int main() {
	FILE *wfp;

	int i=0;

		wfp=fopen(wfn,"w");
		fclose(wfp);

	return 0;
}
