#include <stdio.h>
#include <fcntl.h>

int main() {

	int wfd;
	FILE *wfp;

	close(1);			// close stdout

	wfd=open("myfile1.out",O_CREAT|O_WRONLY|O_TRUNC,0777); 
	// write(1,"Hello World\n",12);
	printf("Hello World\n");
									// fflush(stdout);
									// fclose(stdout);
	close(1);

  // return 1;

	wfp=fopen("myfile2.out","w");
	// fprintf(wfp,"%s\n","Hello World Again!!");
	fprintf(stdout,"%s","Hello World Yet Again!\n");
	// fprintf(stderr,"Got fd=%d\n",fileno(wfp));
	// fclose(stdout);
	fclose(wfp);
}
