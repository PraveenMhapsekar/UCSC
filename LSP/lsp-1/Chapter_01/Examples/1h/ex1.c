#include <stdio.h>
#include <unistd.h>

int main () {

		printf("%ld-bit OS.\n", sysconf(_SC_LONG_BIT));

		return 0;
}
