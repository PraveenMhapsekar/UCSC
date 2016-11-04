// adapted from http://www.helsinki.fi/atk/unix/dec_manuals/DOC_40D/APS33DTE/DOCU_006.HTM

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIG_STOP_CHILD SIGRTMIN+1 

int main() {

pid_t pid;
sigset_t newmask, oldmask;

    if ((pid = fork()) == 0) { /*Child*/
        struct sigaction action;
        void handlesig();

        sigemptyset(&newmask);
        sigaddset(&newmask, SIG_STOP_CHILD);
        sigprocmask(SIG_BLOCK, &newmask, &oldmask);

#ifndef use_KILL
        action.sa_flags = SA_SIGINFO; 
#endif
        action.sa_sigaction = handlesig;

        if (sigaction(SIG_STOP_CHILD, &action, NULL) == -1) { 
            perror("sigusr: sigaction");
            _exit(1);
        }
        sigsuspend(&oldmask);
    }
    else {                             /* Parent */
#ifndef use_KILL
        union sigval sval; 
        sval.sival_int = 1;
        sval.sival_int = 95;
#endif
        int stat;
        sleep(1); 

				// using sigqueue instead of using kill()
#ifdef use_KILL
        kill(pid, SIG_STOP_CHILD);
#else
        sigqueue(pid, SIG_STOP_CHILD, sval);  
#endif

        pid = wait(&stat); 
        printf("Child exit status = %d\n", WEXITSTATUS(stat));
        _exit(0);
    }
}

#ifdef use_KILL
	void handlesig(int signo)
{
       printf("Signal %d, received from parent\n", signo);
       _exit(0);
}
#else
	void handlesig(int signo, siginfo_t *info, void *extra) 
{
       int int_val = info->si_value.sival_int;
       printf("Signal %d, with payload value %d  received from parent\n", signo, int_val);
       _exit(0);
}
#endif
