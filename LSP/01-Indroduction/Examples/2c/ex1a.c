#include <stdio.h>
#include <sys/time.h>

double getmicroseconds() {
   static struct timeval tv[1];  

   gettimeofday(tv, NULL);  
   return   tv->tv_sec + (double)tv->tv_usec/(1000*1000);
}

int main() {
	
	int i=0;
	double t;

	while (i++<10000)
		t=getmicroseconds();

}
		


