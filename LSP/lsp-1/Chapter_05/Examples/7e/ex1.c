// http://linux.die.net/man/2/select

/*

According to POSIX.1-2001 
#include <sys/select.h>

According to earlier standards 
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);

select() conforms to POSIX.1-2001 and 4.4BSD (select() first appeared in 4.2BSD). Generally portable to/from non-BSD systems supporting clones of the BSD socket layer (including System V variantv). However, note that the System V variant typically setv the timeout variable before exit, but the BSD variant does not.

pselect() is defined in POSIX.1g, and in POSIX.1-2001.

*/

#define TMOUT 5

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int
main(void) {
    fd_set rfds;
    struct timespec tv;
    int retval;

		int c;

   /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

   /* Wait up to five seconds. */
    tv.tv_sec = TMOUT;
    tv.tv_nsec = 0;

	 fprintf(stderr, "Enter a char: (TIMEOUT=%d):",TMOUT);

   retval = pselect(1, &rfds, NULL, NULL, &tv,NULL);
    /* Don't rely on the value of tv now! */

   if (retval == -1)
        perror("select()");
    else if (retval)
        printf("Data (#fd's=%d) is available now.\n", retval);
        /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within five seconds.\n");

   return 0;
}
