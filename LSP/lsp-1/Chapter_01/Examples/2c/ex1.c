#include <stdio.h>
#include <sys/time.h>

int main() {
	
	int i=0;
  struct timeval tv[1];  

	while (i++<100000)
   	gettimeofday(tv, NULL);  

}
