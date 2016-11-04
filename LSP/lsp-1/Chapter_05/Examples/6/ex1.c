// ch5_6.c
#define  TMPFILNAME "mytempfile_XXXXXX"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

char *ProgName;
char *FuncName;

int my_mvcmd(char *ofn, char *fn, char *buf);
int my_cpcmd(char *ofn, char *fn, char *buf);

int main(int argc, char **argv) {
	int 	status;
	char	*ofn;
	char	*fn;
	char	errbuf[1024];

	ProgName=argv[0];

	if (argc!=3) {
		fprintf(stderr,"\nUsage: %s <src> <dest>\n",
          ProgName);
		exit(1);
	}
    ofn=argv[1];
    fn=argv[2];
    if ((status=my_mvcmd(ofn,fn,errbuf))==0) 
         fprintf(stderr,"%s:'%s' renamed to '%s'.\n",
			ProgName,ofn, fn);
    else {	
		fprintf(stderr,"%s: ‘%s’ rename failed:%s:#:\n",
			ProgName, ofn, errbuf);
         exit(1);
    }
    exit(0);
}

int my_mvcmd(char *ofn, char *fn, char *erbuf) {
	char       rbuf[1024];
	char       tfn[1024];

	int 	   st=0;
	int 	   rc=0;

	sigset_t   oset;
	sigset_t   set;

	FuncName="my_mvcmd";
	

	sigemptyset(&set);
	sigaddset(&set, SIGHUP);  // hangup
	sigaddset(&set, SIGINT);  // interrupt .. ^C
	sigaddset(&set, SIGQUIT); // quit .. ^\	
	sigaddset(&set, SIGTERM); // kill
	sigaddset(&set, SIGALRM); // alarm
	sigaddset(&set, SIGTSTP); // terminal stp ^Z

	if (access(fn,F_OK) == 0) {
		sprintf(erbuf,"%s.%s: '%s' rename failed:%s::",
 			ProgName,FuncName,ofn,"File Exists");
		return -1;
	}

/* 
	SIG_BLOCK: The new signal mask for the thread will consist of the union of the current set and the signal set pointed to by set.

   SIG_SETMASK: The new signal mask for the thread will consist of the signal set pointed to by set.

   SIG_UNBLOCK: The new signal mask will consist of the intersection of the current set and the complement of the signal set pointed to by set.
*/
	// sigprocmask(SIG_BLOCK, &set, &oset);
   /* Set the signal mask of the thread */
   (void) pthread_sigmask(SIG_BLOCK, &set, &oset );

   /* Get the modified signal of the thread */
   (void) pthread_sigmask(SIG_BLOCK, NULL, &set );

	fprintf(stderr,"In Critical Section. Hit ^C or Enter to Continue\n");
	rc=getchar();	
	
	//	begin critical section
	if (access(ofn,F_OK) == 0) { // is file accessible? 
		sprintf(tfn,"%s",TMPFILNAME);

		rc=mkstemp(tfn);  // tmp name generation: 
 				// Step #2 of 2: use a generated suffix 

		if ((st=rename(ofn,tfn))!= 0) { // rename() .. mv
			sprintf(erbuf,"%s.%s:'%s' rename failed:%s::",
 				ProgName,FuncName,ofn, strerror(errno));
			return -1;
		}	       

		if ((st=my_cpcmd(tfn,fn,rbuf))!=0) { // now copy
			sprintf(erbuf,"%s.%s:'%s' copy failed:%s::",
 				ProgName,FuncName,ofn, strerror(errno));

			// Ok .. copy failed .. time to undo

			// remove reference to newfile .. in case,
			// it got generated above.
			unlink(fn);                     

			// now try to restore back 
			if ((st=rename(tfn,ofn)) != 0) {
				sprintf(erbuf,"%s.%s:'%s' restore fail:%s:",
 					ProgName,FuncName,ofn, strerror(errno));
			}

			return -1; 
		}	               
		// unlink(tfn);   // remove temp file
	}

// end critical section
	// sigprocmask(SIG_BLOCK, &oset, 0);
   /* Set the signal mask of the thread */
   (void) pthread_sigmask(SIG_BLOCK, &set, NULL);
	return(0);
}	

int my_cpcmd(char *ofn, char *fn, char *erbuf) {
	FILE *rfp, *wfp;
	int  st,c;
	FuncName="my_cpcmd";

	if ((rfp=fopen(ofn,"r"))==NULL) { // open src for read
		//	Format error message for open() fail
		sprintf(erbuf,"%s.%s:read: open '%s' fail:%s:",
			ProgName,FuncName,ofn, strerror(errno));
		return -1;
	}

	if ((wfp=fopen(fn,"w"))==NULL) { //open dest for write
		//	Format Meaningful error message for open() fail
		sprintf(erbuf,"%s.%s:write: open '%s' fail:%s",
			ProgName,FuncName,fn, strerror(errno));
		return -1;
	}

	errno=0; 		// reset errno
	while((c=getc(rfp))!=EOF) {		// get next char
		errno=0;					// reset errno
		putc(c,wfp);					// putc
		if (errno!=0) {
			sprintf(erbuf,"%s.%s:write:write '%s' fail:%s:",    
				ProgName,FuncName,fn, strerror(errno));     	
			return -1;
		}
	}

	if (errno!=0) {
		sprintf(erbuf,"%s.%s:read: read '%s' fail:%s:",    
			ProgName,FuncName,ofn, strerror(errno));     	
		return -1;
	}

	fclose(rfp);
	fclose(wfp);

	return 0;
}
