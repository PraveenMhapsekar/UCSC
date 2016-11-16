// ch5_10.c

#define  _POSIX_SOURCE   1
#define  ALARMTMOUT      15
#include <stdio.h>
#include <signal.h>

#ifndef SA_RESTART
#   define SA_RESTART 0x00000004
#endif

void alarm_handler(int sig) {
   fprintf(stderr, "BUZZ! Got Sig '%d'\n",sig);
}

int main() {

   int c;
   struct sigaction oact, act;
   int r;   // alarm_time_remaining

   // set new handler info in struct sigaction
   act.sa_handler=alarm_handler;
   sigemptyset(&act.sa_mask);
   act.sa_flags=SA_RESTART;

   // notify kernel on handler for SIGALRM
   sigaction(SIGALRM, &act, &oact);

   fprintf(stderr, "Setting Alarm for %d secs PID==%d\n",
	ALARMTMOUT,getpid());
 
   r=alarm(ALARMTMOUT);

   pause();

   fprintf(stderr, "pause() returned!\n");

   // Alarm time expired.   
   // Reset old alarm time expired.	

   alarm(r);  // alarm_time_remaining
   sigaction(SIGALRM, &oact, 0);  // reset handler

}
