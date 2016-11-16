//ch5_9.c

#define  _POSIX_SOURCE	1
#define  ALARMTMOUT		15

#include <stdio.h>

int main() {

   int c;
	 int r=-1;

   r=alarm(ALARMTMOUT);

   fprintf(stderr, "Outstanding Alarm:'%d' secs\n",r);
   fprintf(stderr, "Enter Input:(in '%d' secs)\n",
		  ALARMTMOUT);

   while ((c=getchar()) != EOF) {
      putchar(c);
   }

   fprintf(stderr, "EOF received. Awaiting Signal!\n");
	 pause();

   // Alarm time did not expire. 
   // If alarm time expired, the default signal 
   // handler action would have caused the program 
  	// to exit.

   alarm(0); // cancel any previously set alarms

   // 	Notify .. Exit
      fprintf(stderr, "EOF received. Exiting!\n");
	}
