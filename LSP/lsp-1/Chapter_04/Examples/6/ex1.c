#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t counter_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condvar_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condvar_cv  = PTHREAD_COND_INITIALIZER;

void *fn1();
void *fn2();
int  count = 0;

#define COUNT_END  10
#define COUNT_LIMIT1  2
#define COUNT_LIMIT2  7

int main()
{
   pthread_t t1, t2;

   pthread_create( &t1, NULL, &fn1, NULL);
	 sleep(1);
   pthread_create( &t2, NULL, &fn2, NULL);

   pthread_join( t1, NULL);
   pthread_join( t2, NULL);

   return 0;
}


void *fn1() {	// consumer

   while(1) {
      while( count >= COUNT_LIMIT1 && count <= COUNT_LIMIT2 ) {
      	 fprintf(stderr,"consumer: Current Counter Value: %d\n",count);

      	 pthread_mutex_lock( &condvar_mtx );
         pthread_cond_wait( &condvar_cv, &condvar_mtx );
      	 pthread_mutex_unlock( &condvar_mtx );
			}


      pthread_mutex_lock( &counter_mtx );
      count++;
      pthread_mutex_unlock( &counter_mtx );

      fprintf(stderr,"fn1: Counter value: %d\n",count);

			sleep(1);

      if(count >= COUNT_END) break;

    }

		return;

}


void *fn2() {    // producer
    while(1) {

       if( count < COUNT_LIMIT1 || count > COUNT_LIMIT2 ) {
 		      pthread_mutex_lock( &condvar_mtx );
          pthread_cond_signal( &condvar_cv );
       		pthread_mutex_unlock( &condvar_mtx );
			 }

       pthread_mutex_lock( &counter_mtx );
       count++;
       pthread_mutex_unlock( &counter_mtx );

       printf("producer: Counter value: %d\n",count);
	
			 sleep(2);

       if(count >= COUNT_END) break;
    }

		return;

}
