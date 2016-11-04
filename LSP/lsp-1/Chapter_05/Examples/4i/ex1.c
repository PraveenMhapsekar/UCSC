// sourced from http://www.apuebook.com/threadsig.html
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define NTHR 8
#define err_sys(a)	\
{	\
	perror(a); \
	exit(-1); \
}

#define err_exit(a,b)	\
{	\
	fprintf(stderr,"Thread %d: %s",a,b); \
	exit(-1); \
}

#define err_quit(a,b)	\
{	\
	fprintf(stderr,a,b); \
	exit(-1); \
}

sigset_t mask;
pthread_t tid[NTHR];
int block[NTHR];
int alarmthread;

void
delay(int nsec)
{
    struct timespec ts;

    ts.tv_sec = nsec;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);
}

void
handler(int signo)
{
    int i;
    pthread_t id;

    id = pthread_self();
    for (i = 0; i < NTHR; i++)
        if (tid[i] == id)
            break;
    if (i >= NTHR)
        printf("main thread: caught signal %d\n", signo);
    else
        printf("thread %d: caught signal %d\n", i+1, signo);
}

void *
thr_fn(void *arg)
{
		char buf[256];
    int id;

    id = (int)arg;
    printf("thread %d started...\n", id);
    if (block[id-1] != 0) {
        printf("thread %d blocking SIGALRM...\n", id);
        if (pthread_sigmask(SIG_BLOCK, &mask, NULL))
				{
						strerror(buf,"thread %d: can't block SIGALRM", id);
						exit(id);
				}
    }
    if (alarmthread == id) {
        printf("thread %d: setting alarm...\n", id);
        alarm(5);
    }
    pause();
    printf("thread %d: exiting\n", id);
    exit(id);
}

int
main(int argc, char *argv[])
{
    struct sigaction act;
    int i, err, id;
    int doblock = 0;

    setbuf(stdout, NULL);
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "main") == 0) {
            doblock = 1;
        } else if (argv[i][0] == 'a') {
            alarmthread = atoi(&argv[i][1]);
            if (alarmthread > NTHR || alarmthread < 1)
                err_quit("thread ID must be between 1 and %d\n", NTHR);
        } else {
            id = atoi(argv[i]);
            if (id > NTHR || id < 1)
                err_quit("thread ID must be between 1 and %d\n", NTHR);
            block[id-1] = 1;
        }
    }
    if (sigaction(SIGALRM, &act, NULL) < 0)
        err_sys("can't install signal handler");
    for (i = 0; i < NTHR; i++) {
        err = pthread_create(&tid[i], NULL, thr_fn, (void *)(i+1));
        if (err != 0)
            err_exit(err, "can't create thread");
    }
    if (doblock != 0) {
        printf("main thread blocking SIGALRM...\n");
        if (pthread_sigmask(SIG_BLOCK, &mask, NULL))
            err_sys("main thread: can't block SIGALRM");
    }
    if (alarmthread == 0) {
        printf("main thread: setting alarm...\n");
        alarm(5);
    }
    delay(10);
    printf("main thread: return from delay\n");
    exit(0);
}
