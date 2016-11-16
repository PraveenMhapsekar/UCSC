#include <stdio.h>

void printmsg(void);

int main() {

	int pid, n;
	int status;

  int i=0;

	switch (pid=fork()) {

		case -1:
			fprintf(stderr,"fork() failed\n");
			break;
		case 0:
			fprintf(stderr,"Hello World .. child curr PID(%d), PPID(%d)\n",
				getpid(),getppid());
			sleep(5);
			break;
		default:
			sleep(2);
			fprintf(stderr,"Hello World .. parent curr PID(%d), PPID(%d)\n",
				getpid(),getppid());
			printmsg();
			break;
	}

	return 0;

}	

void printmsg() {

		int i=0;

		while (i++<5) {
			fprintf(stderr,"Hello World .. parent curr PID(%d), PPID(%d)\n",getpid(),getppid());
			sleep(2);
			system("ps -f");
		}
}

