//ch5_9.c

#define  _POSIX_SOURCE	1
#define  ALARMTMOUT1	15
#define  ALARMTMOUT2	10

#include <stdio.h>

int main() {

   int c;
	 int r1=-1;
	 int r2=-1;
	 int r3=-1;

   r1=alarm(ALARMTMOUT1); // outstanding alarm value .. is 0
	 sleep(3);
   r2=alarm(ALARMTMOUT1); // outstanding alarm value .. is 12

   fprintf(stderr, "Outstanding Alarm:'%d' secs\n",r2);
   fprintf(stderr, "Enter Input:(in '%d' secs)\n",
		  ALARMTMOUT1);

   while ((c=getchar()) != EOF) {
      putchar(c);
   }
   fprintf(stderr, "EOF received. Awaiting Signal!\n");

   r3=alarm(ALARMTMOUT2);
   fprintf(stderr, "Initial Alarm - r1:'%d' secs\n",r1);
   fprintf(stderr, "Outstanding Alarm - r2:'%d' secs\n",r2);
   fprintf(stderr, "Outstanding Alarm - r3:'%d' secs\n",r3);

	 pause();

   // Alarm time did not expire. 
   // If alarm time expired, the default signal 
   // handler action would have caused the program 
  	// to exit.

   alarm(r3); // reset any previously set alarms

   // 	Notify .. Exit
      fprintf(stderr, "EOF received. Exiting!\n");
	}
