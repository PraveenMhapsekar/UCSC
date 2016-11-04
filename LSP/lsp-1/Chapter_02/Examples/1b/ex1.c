// ch2_1a.c

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	FILE *rfp;

	rfp=fopen(rfn, "w");
	printf("Opened File '%s'. sizeof(FILE)==%d.\n", rfn, sizeof(FILE));
	fclose(rfp);
}
