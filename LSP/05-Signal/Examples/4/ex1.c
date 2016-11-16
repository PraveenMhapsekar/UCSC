//ch5_9.c

#define  _POSIX_SOURCE	1
#define  ALARMTMOUT		10

#include <stdio.h>
#include <stdlib.h>

int main() {

   int c;
   alarm(ALARMTMOUT);

   fprintf(stderr, "Enter Input:(in '%d' secs) PID==%d\n",
		  ALARMTMOUT,getpid());

   while ((c=getchar()) != EOF) {
      putchar(c);
   }

   // Alarm time did not expire. 
   // If alarm time expired, the default signal 
   // handler action would have caused the process
   // to exit.

   alarm(0); // cancel any previously set alarms

   // 	Notify .. Exit
      fprintf(stderr, "EOF received. Exiting!\n");

		return 0;
	}
