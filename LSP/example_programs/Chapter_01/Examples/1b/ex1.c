#include <stdio.h>
#include <limits.h>

int main() {

/*
#if defined(_CHAR_IS_SIGNED)
	printf("signed char,");
#elif defined(_CHAR_IS_UNSIGNED)
	printf("unsigned char,");
#endif
*/

// obtained from /usr/include/limits.h
#if defined(__CHAR_UNSIGNED__) 
	printf("unsigned char,\n");
#else
	printf("signed char,\n");
#endif

	return 0;

}

