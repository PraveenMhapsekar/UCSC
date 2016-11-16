#include <stdio.h>
#include <unistd.h>

int main () {

		printf("CHAR is '%s'.\n",
       (sysconf(_SC_CHAR_MIN)==-128) ? "SIGNED" : "UNSIGNED");

		return 0;
}
