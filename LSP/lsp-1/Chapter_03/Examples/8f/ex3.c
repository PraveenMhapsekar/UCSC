#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void ForkAndWait();
void PrintStatus(FILE *wfp, int mypid, int status);


int main() {
	fprintf(stderr, "My PID is %d.\n", (int) getpid() );
	ForkAndWait();
	ForkAndWait();
	ForkAndWait();
}

void ForkAndWait() {
	pid_t mypid;
	int status;

	char *ptr=malloc(2048000);
	ptr[100000]=0;

	mypid = fork();
	
	

	switch ((int) mypid) {
		case -1:
			fprintf(stderr, "Err: fork() failed:%s\n", strerror(errno));
			break;
		case 0:
			fprintf(stderr, "Child Process!\n");
			sleep(15);
			_exit(0);
			break;
		default:
			fprintf(stderr, "Parent Process!\n");
			sleep(4);
			kill(mypid,SIGSEGV);
			mypid=wait(&status);
			PrintStatus(stdout, mypid,status);
			exit(0);
	}
}

void PrintStatus(FILE *wfp, int mypid, int status) {

	fprintf(wfp, "\n");
	fprintf(wfp, "%6d = wait()", mypid);

	if (WIFEXITED(status)) {
		fprintf(wfp, "Exit Status = %3d\n", WEXITSTATUS(status));
	}

	if (WIFSTOPPED(status)) {
		fprintf(wfp, "Stop Signal = %3d\n", WSTOPSIG(status));
	}

	if (WIFSIGNALED(status)) {
		fprintf(wfp, "Exit Signal = %3d\n", WTERMSIG(status));
		fprintf(wfp, "Core Dump : %s\n", WCOREDUMP(status) ? "Yes" : "No");
	}

}
