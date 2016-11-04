// ch5_10.c

#define  _POSIX_SOURCE   1
#define  ALARMTMOUT      5
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
 
   // alarm() returns time remaining on 
   //   current alarm (if any) 
   r=alarm(ALARMTMOUT);

   // ZZZ .. process is now sleeping!
   // - No CPU resources are consumed.

   // pause() .. returns when any signal 
   //            is received


/*

#include <signal.h>
int sigpause(int sigmask);  //  BSD 
int sigpause(int sig);      // Unix95 

Description
Don't use this function. Use sigsuspend(2) instead.

The function sigpause is designed to wait for some signal. It changes the process' signal mask (set of blocked signals), and then waits for a signal to arrive. Upon arrival of a signal, the original signal mask is restored. 

History
The classical BSD version of this function appeared in 4.2BSD. It sets the process' signal mask to sigmask. When the number of signals was increased above 32, this version was replaced by the incompatible Unix95 one, which removes only the specified signal sig from the process' signal mask. The unfortunate situation with two incompatible functions with the same name was solved by the sigsuspend(2) function, that takes a sigset_t * parameter (instead of an int).

On Linux, this routine is a system call only on the Sparc (sparc64) architecture. Libc4 and libc5 only know about the BSD version. Glibc uses the BSD version unless _XOPEN_SOURCE is defined. 
*/
   sigpause(SIGALRM);

   fprintf(stderr, "sigpause() returned!\n");

   // Alarm time expired.   
   // Reset old alarm time expired.	

   alarm(r);  // alarm_time_remaining
   sigaction(SIGALRM, &oact, 0);  // reset handler

}

