// sourced from http://www.helsinki.fi/atk/unix/dec_manuals/DOC_40D/APS33DTE/DOCU_006.HTM

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// #define MYSIGNAL SIGINT
// #define MYSIGNAL SIGRTMIN
// #define MYSIGNAL SIGRTMAX
// #define MYSIGNAL SIGRTMIN+1
// #define MYSIGNAL SIGRTMIN+16
// #define MYSIGNAL SIGRTMIN+30
// #define MYSIGNAL SIGRTMAX
// #define MYSIGNAL SIGRTMAX-30
// #define MYSIGNAL SIGRTMIN+3
// #define MYSIGNAL SIGRTMAX-3
#define MYSIGNAL SIGRTMIN

main()
{
pid_t pid;
sigset_t newmask;
int rcvd_sig; 
siginfo_t info; 

    if ((pid = fork()) == 0) {       /*Child*/

        sigemptyset(&newmask);
        sigaddset(&newmask, MYSIGNAL);
        sigprocmask(SIG_BLOCK, &newmask, NULL); 

        while (1) { 
            rcvd_sig = sigwaitinfo(&newmask, &info); // blocking call
            if (rcvd_sig == -1) {
               perror("sigusr: sigwaitinfo");
               _exit(1);
            }
            else { 
                 printf("Signal %d, payload value %d  received from parent\n",
                     rcvd_sig, info.si_value.sival_int);
               _exit(0);
            }
        }
    }
    else {                           /* Parent */
        union sigval sval;
        sval.sival_int = 10000;
        sval.sival_int = -10000;
        sval.sival_int = 1;
        sval.sival_int = 100;
        sval.sival_int = 100000000;
        sval.sival_int = -10000;
        sval.sival_int = 100;
        int stat;
				fprintf(stderr,"sleep(10).");
        sleep(10);
        sigqueue(pid, MYSIGNAL, sval);
        pid = wait(&stat);
        printf("Child exit status = %d\n", WEXITSTATUS(stat));
        _exit(0);
    }
}
