// ch2_2.c

#include <stdio.h>

char *rfn= "myfile.txt";

int main() {
	FILE *wfp2;
	FILE *wfp3;
	FILE *wfp1;

	wfp1=fopen(rfn, "w");
	wfp2=fopen(rfn, "w");
	wfp3=fopen(rfn, "w");
	
	// wfp3=fopen(rfn, "w");
	// wfp2=fopen(rfn, "w");
	// wfp1=fopen(rfn, "w");
	
  // fprintf(wfp1,"Hello World");
  fprintf(wfp1,"Hello TESTING LONG LONG LONG LONG TIME");
  fflush(wfp1);

  // fprintf(wfp2,"Testing 123");
  fprintf(wfp2,"World ajfdadfjjhlkhakjf afdkjkjfhajsdhfhhjd");
  // fflush(wfp2);

  // fprintf(wfp3,"Again 12343");
  fprintf(wfp3,"Again 1234321409832174 1234809321049873309481389");

	// fclose(wfp1);
	// fclose(wfp2);
	// fclose(wfp3);

  return;
}
