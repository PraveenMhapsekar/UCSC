// ch2_2.c

#include <stdio.h>

char *rfn= "myfile.txt";

int main() {
	FILE *rfp1;
	FILE *rfp2;
	FILE *rfp3;

	rfp1=fopen(rfn, "r");
	rfp2=fopen(rfn, "r");
	rfp3=fopen(rfn, "r");

	fclose(rfp1);
	fclose(rfp2);
	fclose(rfp3);
}
