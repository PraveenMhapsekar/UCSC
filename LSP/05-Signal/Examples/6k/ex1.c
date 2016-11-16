// sourced from http://www.cognitus.net/html/howto/pthreadSemiFAQ_8.html

#define NUM_LOOPS 5

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main ( int argc, char ** argv )
{
   int count;
   int result;

   sigset_t mask;
   siginfo_t info;
   struct timespec timeout;


	 fprintf(stderr,"PID==%d\n",getpid());
   /* Create a mask holding only SIGINT - ^C Interrupt */
   sigemptyset( & mask );
   sigaddset( & mask, SIGINT );

   /* Set the mask for our main thread to include SIGINT */
   pthread_sigmask( SIG_BLOCK, & mask, NULL );

   /* Max wait for ^C set to 7 seconds */

   timeout.tv_sec = 7;
   timeout.tv_nsec = 0;

   /*
      Receive max combination of NUM_LOOP signals
      or timeouts from sigtimedwait
   */

   for ( count = 0; count < NUM_LOOPS; ++ count )
   {
     result = sigtimedwait( & mask, & info, & timeout );

     if ( (-1 == result) && (EAGAIN == errno) )
     {
       printf( "No ^C received. Timeout occurred in sigtimedwait( ) call.\n" );
     }
     else
     {
       switch ( info.si_signo )
       {
         case SIGINT:
           printf( "Caught SIGINT in sigtimedwait( )\n" );
         break;

         /* Should never really get to default */

         default:
           printf( "Caught unexpected signal %i\n", info.si_signo );
         break;
       }
     }
   }

   return 0;
}

