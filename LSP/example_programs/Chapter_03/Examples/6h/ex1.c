#include <stdio.h>

int main() {
	int i=0;

	while (i++<100) {
		sleep(1);
	  fprintf(stderr,"=> %d. \n",i);
 }

	return 0;
}
