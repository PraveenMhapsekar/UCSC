/*
 * mtf-main.c
 *
 *  Created on: Aug 2, 2010
 *      Author: Gregg Weissman
 *      Linux systems programming
 *
 *      Multi-threaded find: spawn a thread for each top-level
 *      directory, searching for matches on filenames.
 *
 *      Consists of the following modules:
 *      - mtf-dirwalk: iterates the specified directory and issues a callback
 *        for each entity found.
 *      - mtf-direntry: processes the callbacks for each entry found
 *        including recursing back into dirwalk.
 *      - mtf-match: called to see if a match exists on the current
 *        entry.
 *      - mtf-main: this module.  Retrieve command args and start everything.
 *
 *      Usage:
 *
 *      mtfind [flags] [startdir [lookfor [...]]]
 *
 *      flags: -l		long listing info
 *      	   -t n		use up to "n" threads (I may not bother with this right now)
 *
 *      If no startdir is provided, use "."
 *      If no lookfor is provided, use ".+", match everything.
 *      Note that if there are lookfor parameters, there must be a startdir
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "mtf-config.h"
#include "mtf-dirwalk.h"
#include "mtf-match.h"

/* configuration structure */
s_mtfConfig 	config;

/**
 * main
 *
 */

int main( int argc, char *argv[] )
{
	char 		*dfltFind=".+";
	int			retval;

	/* from getopt: */
	extern char *optarg;
	extern int optind, opterr, optopt;

	/* init all defaults */
	config.longFlag = 0;
	/* if we ever get to throttling the thread count */
	config.nThreads = 1;

	config.startPath = ".";
	config.findList=&dfltFind;
	config.nFinds = 1;

	/* parse the command line */
	int opt;

	while ( (opt=getopt(argc,argv,"lt:")) != -1 ) {
		switch(opt) {
		case 'l':
			config.longFlag = 1;
			break;
		case 't':
			config.nThreads = atoi(optarg);
			break;
		default:
			fprintf(stderr,"%s [-l] [-t nthreads] [startdir [lookfor [...]]]\n",argv[0]);
			return(-1);
		}
	}

	if ( optind < argc ) {
		config.startPath = argv[optind++];
	}

	if (optind < argc ) {
		config.nFinds = argc-optind;
		config.findList = argv+optind;
	}

#if DEBUG
	printf("longFlag = %d  nThreads=%d startPath = %s\n",
			config.longFlag, config.nThreads, config.startPath);
	{
		int i;
		for(i=0;i<config.nFinds;i++) {
			printf(" find: %s\n", config.findList[i]);
		}
	}
#endif

	/* set up the pthreads stuff */
	config.threadsRunning = 0;
	config.topThread = pthread_self();
	if  ( pthread_mutex_init(&config.configMutex,NULL) != 0 ) {
		fprintf(stderr,"pthread_mutex_init failed %d\n",errno);
		exit(-1);
	}

	/* set up reg expressions from and to global config struct */
	retval = initRegexps();
	if ( retval < 0 ) {
		fprintf(stderr,"errr %d initializing reg exps\n",retval);
		exit(-1);
	}

	/* zero the count */
	config.totalCount = 0;
	retval = mtf_dirwalk();

	/* wait for all the threads - interestingly, */
	/* waiting for thread count to go to 0 does  */
	/* not require the main thread to synchronize.*/

	while( config.threadsRunning > 0) {
		/* waiting */ ;
	}
	pthread_mutex_destroy(&config.configMutex);
	destroyRegexps();
	printf("total matches found: %d, ret val: %d\n", config.totalCount, retval);
	return(retval);
}

