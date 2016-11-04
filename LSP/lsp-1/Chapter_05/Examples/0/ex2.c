#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// #define SIGNAL SIGHUP
// #define SIGNAL SIGSEGV
#define SIGNAL 2

int main()
{
	int s=SIGNAL;
	pid_t pid;

  fprintf(stderr,"PID=%d\n",getpid());
	switch(pid=fork())
	{
		case -1:
			fprintf(stderr,"fork error\n");
			return -1;
		case 0: // child
			while(1);	
			break;
		default : // parent
			sleep(2);	
			system("ps -f");
			fprintf(stderr,"sending signal=%d to PID=%d.\n",s,pid);
			kill(pid,s);
			sleep(1);	
			system("ps -f");
			sleep(1);
			break;
	}
}
