#include <stdio.h>

int main() {

	char *wfn="myfile.txt";

	FILE *wfp;

	int c;

	wfp=fopen(wfn,"w");

	fprintf(stderr,"PID==%d\n",getpid());

	c=getchar();
	
	fclose(wfp);

}
