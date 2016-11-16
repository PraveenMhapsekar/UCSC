#include <stdio.h>
#include <signal.h>
#include <errno.h>

int main() {
	int c;

	// ignore ^C
	signal(SIGINT,SIG_IGN);
	fprintf(stderr, "Enter an input char(it ignores ^C):\n");

	while ((c=getchar())!=EOF) {
		putchar(c);
	}

	signal(SIGINT,SIG_DFL);
	fprintf(stderr, "EOF Entered!  End Program!!:\n");

	return 0;
}
