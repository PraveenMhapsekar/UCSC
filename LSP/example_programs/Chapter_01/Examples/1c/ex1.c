#include <stdio.h>
#include <limits.h>

int main() {

// obtained from /usr/include/limits.h
#if defined(__CHAR_UNSIGNED__) 
	printf("unsigned char,\n");
#else
	printf("signed char,\n");
#endif

	printf(
		"-sizeof(short)=%d,\n"
		"-sizeof(int)=%d,\n"
		"-sizeof(long int)=%d,\n"
		"-sizeof(long)=%d,\n"
		"-sizeof(float)=%d,\n"
		"-sizeof(double)=%d,\n"
		"-sizeof(long double)=%d,\n"
		"-sizeof(long long)=%d\n",
		sizeof(short), sizeof(int), sizeof(long int),
		sizeof(long), sizeof(float),
	  sizeof(double),
	  sizeof(long double),
		sizeof(long long));

	return 0;

}

