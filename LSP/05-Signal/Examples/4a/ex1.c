//ch5_9.c

#define  _POSIX_SOURCE	1
#define  ALARMTMOUT		18

#include <stdio.h>

int main() {

   int c;
   alarm(ALARMTMOUT);

   fprintf(stderr, "Enter Input:PID=%d (in '%d' secs)\n",
		  getpid(),ALARMTMOUT);

   while ((c=getchar()) != EOF) {
      putchar(c);
   }

   fprintf(stderr, "EOF received. Awaiting Signal! (PID==%d)\n",
		getpid());
	 pause();

   // Alarm time did not expire. 
   // If alarm time expired, the default signal 
   // handler action would have caused the program 
  	// to exit.

   fprintf(stderr, "SIGALRM received. (PID==%d)\n", getpid());
   alarm(0); // cancel any previously set alarms

   // 	Notify .. Exit
   fprintf(stderr, "EOF received. Exiting!\n");
	}
