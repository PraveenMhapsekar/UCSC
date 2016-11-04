// ch2_2.c

#include <stdio.h>

char *rfn= "myfile.txt";

int main() {
	FILE *rfp;
	rfp=fopen(rfn, "r");

	if (rfp)
		fclose(rfp);
}
