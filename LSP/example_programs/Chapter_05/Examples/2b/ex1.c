#include <stdio.h>
#include <signal.h>
#include <errno.h>

void intr_handler(int sig) {
	int c;
	fprintf(stderr,"\n Handling Signal: %d\n", sig);
	fprintf(stderr,"\n Enter a char (in the handler):");
	c=getchar();
	// putchar(c);
	fprintf(stderr,"c=%c",c);  // negate effects of stdout buffering.
}

int main() {
	int c;

	signal(SIGINT,intr_handler);
	fprintf(stderr, "Enter an input char(including ^C - for Handler):\n");

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	signal(SIGINT,SIG_DFL);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

	return 0;
}
