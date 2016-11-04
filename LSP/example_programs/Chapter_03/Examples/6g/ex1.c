#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {

	int i=0;
	pid_t mypid;
	fprintf(stderr,"Hello World pid=%d!\n",(int) getpid() );


	mypid=fork();

	fprintf(stderr,"Hello World pid=%d!\n",(int) getpid() );

	if (mypid==-1)  {
		fprintf(stderr,"fork failed=%d (%s)!",
			errno,strerror(errno));
	}

	if (mypid == 0)  {
		sleep(5);
		for (i=0;i++<5;) {
			printf("%d. Hello!\n",i);
		  sleep(5);
		}
  }

	return 0;
}
