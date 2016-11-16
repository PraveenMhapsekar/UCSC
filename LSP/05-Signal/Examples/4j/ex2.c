// sourced from http://www.apuebook.com/threadsig.html
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>

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

#if !defined(MAP_FAILED)
#define MAP_FAILED ((void *)-1)
#endif

#define NTHR 8
#define MAPSZ (8*1024*1024)

sigset_t mask;
pthread_t tid[NTHR];
int block[NTHR];
int faultthread;
char *mapaddr;

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
    exit(1);
}

void
oops(void)
{
    char c;

    c = *mapaddr;
}

void *
thr_fn(void *arg)
{
    int id;

    id = (int)arg;
    printf("thread %d started...\n", id);
    if (block[id-1] != 0) {
        printf("thread %d blocking SIGSEGV...\n", id);
        if (pthread_sigmask(SIG_BLOCK, &mask, NULL))
				{
            fprintf(stderr,"thread %d: can't block SIGSEGV", id);
            err_sys("can't block SIGSEGV");
				}
    }
    if (faultthread == id) {
        delay(2);
        printf("thread %d: generating fault...\n", id);
        oops();
    }
    pause();
    printf("thread %d: exiting\n", id);
    exit(id);
}

int
main(int argc, char *argv[])
{
    struct sigaction act;
    int i, err, id, fd;
    int doblock = 0;

    if ((fd = open("tempfile", O_RDWR|O_CREAT)) < 0)
		{
        fprintf(stderr,"can't open %s", argv[0]);
        err_sys("can't open file");
		}
    if (lseek(fd, MAPSZ-1, SEEK_SET) == -1)
        err_sys("can't seek");
    if (write(fd, "a", 1) != 1)
        err_sys("can't write to temp file");
    mapaddr = mmap(0, MAPSZ, PROT_READ, MAP_SHARED, fd, 0);
    if (mapaddr == MAP_FAILED)
        err_sys("can't map temp file");
    unlink("tempfile");
    close(fd);
    if (munmap(mapaddr, MAPSZ) < 0)    /* invalidate the mapping */
        err_sys("can't unmap file");
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "main") == 0) {
            doblock = 1;
        } else if (argv[i][0] == 'a') {
            faultthread = atoi(&argv[i][1]);
            if (faultthread > NTHR || faultthread < 1)
                err_quit("thread ID must be between 1 and %d\n", NTHR);
        } else {
            id = atoi(argv[i]);
            if (id > NTHR || id < 1)
                err_quit("thread ID must be between 1 and %d\n", NTHR);
            block[id-1] = 1;
        }
    }
    sigemptyset(&mask);
    sigaddset(&mask, SIGSEGV);
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGSEGV, &act, NULL) < 0)
        err_sys("can't install signal handler");
    for (i = 0; i < NTHR; i++) {
        err = pthread_create(&tid[i], NULL, thr_fn, (void *)(i+1));
        if (err != 0)
            err_exit(err, "can't create thread");
    }
    delay(2);
    if (doblock != 0) {
        printf("main thread blocking SIGSEGV...\n");
        if (pthread_sigmask(SIG_BLOCK, &mask, NULL))
            err_sys("main thread: can't block SIGSEGV");
    }
    if (faultthread == 0) {
        printf("main thread: generating fault...\n");
        oops();
    }
    delay(4);
    printf("main thread: return from delay\n");
    exit(0);
}
