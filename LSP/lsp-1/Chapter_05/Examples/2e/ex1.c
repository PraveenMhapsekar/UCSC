#include <stdio.h>
#include <signal.h>
#include <errno.h>

void intr_handler(int sig) {
	static int counter=0;
	int c;
	fprintf(stderr,"\n Handling Signal: %d .. enter a char\n", sig);
	c=getchar();
	fprintf(stderr,"\n done .. counter=%d \n", counter++);
}

int main() {
	int c;

	signal(SIGINT,intr_handler);
	fprintf(stderr, "Enter an input char:\n");

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	signal(SIGINT,SIG_DFL);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

	return 0;
}
