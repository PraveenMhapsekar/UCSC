// adapted from http://www.cognitus.net/html/howto/pthreadSemiFAQ_8.html

#define NUMSIGNALS 32

#include <pthread.h>
#include <signal.h>
#include <stdio.h>

void print_maskedsignals(char *, char *, sigset_t *);

void print_maskedsignals(char *typ, char *checkbits, sigset_t *sigset){
  int sig=0;

	checkbits[sig]='0';
  for (sig=1;sig<NUMSIGNALS;sig++)
		checkbits[sig]=(sigismember(sigset,sig))?'1':'0';

	fprintf(stderr,"%12.12s Mask of Blocked Signals = '%s'\n",typ,checkbits);

  return;
}

int main (int argc, char **argv)
{
	char sigbit[NUMSIGNALS+1];
	char osigbit[NUMSIGNALS+1];

  sigset_t set;
  sigset_t oset;

  sigemptyset( &set );
  sigemptyset( &oset );

	sigbit[NUMSIGNALS]=osigbit[NUMSIGNALS]=0;

  sigaddset(&set, SIGHUP);  // hangup
  sigaddset(&set, SIGINT);  // interrupt .. ^C
  sigaddset(&set, SIGQUIT); // quit .. ^\ 

  /* Set the signal mask of the thread */
  pthread_sigmask( SIG_BLOCK, &set, &oset );

  /* Get the modified signal of the thread */
  pthread_sigmask( SIG_BLOCK, NULL, &set );

	print_maskedsignals("Old",osigbit,&oset);
	print_maskedsignals("New",sigbit,&set);

  sigaddset(&set, SIGTERM); // kill 
  sigaddset(&set, SIGALRM); // alarm
  sigaddset(&set, SIGTSTP); // terminal stp ^Z
  sigaddset(&set, SIGCHLD); // 
  sigaddset(&set, SIGPIPE); //
  sigaddset(&set, SIGIO); // 

  /* Set the signal mask of the thread */
  pthread_sigmask( SIG_BLOCK, &set, &oset );

	print_maskedsignals("Old! Again",osigbit,&oset);
	print_maskedsignals("New! Again",sigbit,&set);
	return 0;
}
