// #define _POSIX_SOURCE 1

// #define uses_SYSV_sigpoll

#define TIMEOUTVALUE 15

#define ERRBUFSZ 512

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>

#ifdef _POSIX_SOURCE 
	#ifndef SA_RESTART
		#define SA_RESTART 0x000004
	#endif
#endif

#ifdef uses_SYSV_sigpoll
	#include <sys/types.h>
	#include <stropts.h>
	#include <sys/conf.h>
#endif

int init_async_IO(int fd, void(*handler_fn)(), char * errbuf);
static void sigio_handler(void);

static void sigio_handler() {

	int c;

	while (1) {
	
		errno=0;

		if ((c=getchar())==EOF) {
			return;
		}

		putchar(c);
	}
}

#ifdef uses_SYSV_sigpoll
	int init_async_IO(int fd, void(*handler_fn)(), char *errbuf) {

		int st;
		
		struct sigaction nsigaction;

		nsigaction.sa_handler=handler_fn;
		sigemptyset(&nsigaction.sa_mask);
		nsigaction.sa_flags=SA_RESTART;

		sigaction(SIGPOLL,&nsigaction,0);

		st=ioctl(fd,I_SETSIG,S_RDNORM);

		if (st !=0) {
			sprintf(errbuf,"ERR: ioctl (%d, I_SETSIG): %s", 
				fd, strerror(errno));	
			return -1;
		}

		return 0;
	}
	
#else
	int init_async_IO(int fd, void(*handler_fn)(), char *errbuf) {

		int st;
		int fl;
		
		struct sigaction nsigaction;

		nsigaction.sa_handler=handler_fn;
		sigemptyset(&nsigaction.sa_mask);
		nsigaction.sa_flags=SA_RESTART;

		sigaction(SIGIO,&nsigaction,0);

		fl=fcntl(fd,F_GETFL,0);	
		fl |= O_ASYNC | O_NONBLOCK;
		st=fcntl(fd,F_SETFL,fl);	

		if (st !=0) {
			sprintf(errbuf,"ERR: fcntl (%d, F_SETFL): %s", 
				fd, strerror(errno));	
			return -1;
		}

		st=fcntl(fd,F_SETOWN,getpid()); /* give your pid to device driver .. to  tell which process should receive signal */

		if (st !=0) {
			sprintf(errbuf,"ERR: fcntl (%d, F_SETOWN): %s", 
				fd, strerror(errno));	
			return -1;
		}
		
		return 0;
	}

#endif

int main(int argc, char **argv) {
	
	int i;
	int k;

	int st;
	char *errbuf=(char *)malloc(ERRBUFSZ*sizeof(char)); 

#ifdef use_SELECT
	int myfd1, myfd2, maxfd, nrdy=0;
	fd_set rfd, wfd, efd;
	struct timeval tmout;
#endif

	st=init_async_IO(STDIN_FILENO, sigio_handler, errbuf);
	if (st !=0) {
		fprintf(stderr,"ERR: init_async_io: %s\n", errbuf);
		return -1;
	}

	// meanwhile, do something else / useful here.

#ifdef use_SELECT
	while (nrdy<=0) {
		tmout.tv_sec=TIMEOUTVALUE;
    tmout.tv_usec=1000;

    FD_ZERO(&rfd);
    FD_ZERO(&wfd);
    FD_ZERO(&efd);
    
    FD_SET(myfd1,&rfd);
    FD_SET(myfd2,&rfd);

    maxfd=1;
    nrdy = select (maxfd, &rfd, &wfd, &efd, &tmout);

    fprintf(stderr,"After Select ..\n");

    if (nrdy<0){
      if(errno==EINTR) {
        continue; // select() not restarted, after an interrupt.
      }
      fprintf(stderr,"select() failed: %s\n", strerror(errno));
    }

    if (nrdy == 0) {
      fprintf(stderr, "Timed Out.\n");
      break;
    }

    if (FD_ISSET(myfd1,&rfd)) {
      fprintf(stderr, "Can Read from fd=%d\n", myfd1);
		}
	}

#else
	for (i=0;i<5;i++) {
		fprintf(stderr,"%d. Hello! from '%s' pid=%d\n",i,argv[0],getpid()); 
		for(k=0;k++<100000000;);
		sleep(2);
	}
#endif
	
	exit (0);
}

