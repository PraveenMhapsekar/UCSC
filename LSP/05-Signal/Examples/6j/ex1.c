// sourced/adapted from http://cs.pub.ro/~apc/2003/resources/pthreads/uguide/users-95.htm

#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/signal.h>

#define NUMTHREADS 7
void sighand(int signo);

void *threadfunc(void *parm)
{
  pthread_t       tid = pthread_self();
  int                   rc;

  // printf("Thread 0x%.8x %.8x entered\n", tid);
  printf("Thread 0x%.8x entered\n", tid);
  errno = 0;
  rc = sleep(10);
  if (rc != 0 && errno == EINTR) {
    printf("Thread 0x%.8x got a signal delivered to it\n", tid);
    return NULL;
  }
  printf("Thread 0x%.8x didn't get signal! rc=%d, errno=%d\n",
         tid, rc, errno);
  return NULL;
}

int main(int argc, char **argv)
{
  int                     rc;
  int                     i;
  struct sigaction        actions;
  pthread_t               threads[NUMTHREADS];

  printf("Enter Testcase - %s\n", argv[0]);
  
  printf("Set up the alarm handler for the process\n");
  memset(&actions, 0, sizeof(actions));
  sigemptyset(&actions.sa_mask);
  actions.sa_flags = 0;
  actions.sa_handler = sighand;

  rc = sigaction(SIGALRM,&actions,NULL);

  for(i=0; i<NUMTHREADS; ++i)  // NUMTHREADS == 7
    rc = pthread_create(&threads[i], NULL, threadfunc, NULL);

  sleep(3);
  for(i=0; i<NUMTHREADS-2; ++i)  // NUMTHREADS == 7
    rc = pthread_kill(threads[i], SIGALRM);
  

  for(i=0; i<NUMTHREADS; ++i)  // NUMTHREADS == 7
    rc = pthread_join(threads[i], NULL);
  
  printf("Main completed\n");
  return 0;
}

void sighand(int signo)
{
  pthread_t             tid = pthread_self();
  printf("Thread 0x%.8x in signal handler\n", tid);
  return;
}
