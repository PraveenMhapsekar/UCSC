// sourced from http://www.helsinki.fi/atk/unix/dec_manuals/DOC_40D/APS33DTE/DOCU_006.HTM

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define SIGQUEUE_MAX 30
// #define SIGQUEUE_MAX 4

main()
{
        sigset_t        set, pend;
        int             i=0, sig, sigq_max=-1, numsigs = 0;
        siginfo_t       info;
        int             SIG = SIGRTMIN;
        // int          SIG = SIGINT;

        // sigq_max = sysconf(_SC_SIGQUEUE_MAX);
        fprintf(stderr,"sigq_max=%d\n",sigq_max);
			  sigq_max =  (sigq_max==-1) ? SIGQUEUE_MAX : sigq_max;
        fprintf(stderr,"Confirm .. sigq_max=%d\n",sigq_max);

        sigemptyset(&set);
	
			  i=0;
			  for(i=0;((i<SIGRTMAX)&&(i<SIGQUEUE_MAX));i++)
        	sigaddset(&set, SIG+i);

        sigprocmask(SIG_SETMASK, &set, NULL);
        printf("\nNow create a child to send signals...\n");

        if (fork() == 0) {      /* child */
				        union sigval sval;
                pid_t parent = getppid();
                printf("Child will signal parent %d\n", parent);
                for (i = 0; i < sigq_max; i++) {
				        				sval.sival_int = i;
                        if (sigqueue(parent, SIG+i, sval) < 0)
                                perror("sigqueue");
                }
                exit(1);
        }

        printf("Parent sigwait for child to queue signal...\n");
   		  sleep(5);
        for (i = 0; i < sigq_max; i++) {
        				sigpending(&pend);
        				printf("Is signal pending: %s\n",
               			sigismember(&pend, SIG+i) ? "yes" : "no");
                sig = sigwaitinfo(&set, &info);
                if (sig < 0) {
                        perror("sigwait");
                        exit(1);
                }
                printf("Main woke up after signal %d\n", sig);
                printf("signo = %d, pid = %d, uid = %d, val = %d,\n",
                       info.si_signo, info.si_pid, info.si_uid, info.si_int);
                numsigs++;
        }
        printf("Main: done after %d signals.\n", numsigs);
			
				return 0;
}
