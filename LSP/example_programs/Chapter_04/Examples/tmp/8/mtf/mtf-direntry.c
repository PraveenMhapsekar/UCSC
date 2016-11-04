/*
 * mtf-direntry.c
 *
 *  Created on: Aug 3, 2010
 *      Author: Gregg Weissman
 *      Linux Systems Programming
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>

#include "mtf-config.h"
#include "mtf-direntry.h"
#include "mtf-dirwalk.h"
#include "mtf-match.h"

/**
 * helper function declarations
 */
static
void modestring( int mode, char *str );
static
char *modebits( int mode );

/**
 * extern config
 */
extern s_mtfConfig config;

/**
 * printMatchingEntry
 *
 * Display a found entry
 */
static
void printMatchingEntry(const char *name,const char *fullPath,const struct stat *statDat)
{
	char modestr[16];
	struct passwd *pwinfo;
	char usrname[256];
	char grpname[256];
	char timestr[64];

	if ( !config.longFlag ) {
		printf("%s\n",name);
		return;
	}

	/* get a string showing mode bits */
	modestring(statDat->st_mode, modestr);

	/* get names for user and group id's */
	pwinfo = getpwuid(statDat->st_uid);
	strcpy( usrname, pwinfo->pw_name );
	pwinfo = getpwuid(statDat->st_gid);
	strcpy( grpname, pwinfo->pw_name );

	/* make the access time into a string */
	strcpy(timestr,ctime(&statDat->st_mtim.tv_sec));
	if ( strchr(timestr,'\n') != NULL )
		*strchr(timestr,'\n') = '\0';

	printf( "%s %-4d  %s %s %-8d %s %s",modestr,statDat->st_nlink,usrname,
			grpname,statDat->st_size,
			timestr,
			name);
	if (  S_ISLNK(statDat->st_mode) ) {
		char nupath[1024];
		int rslt;
		rslt = readlink(fullPath,nupath,sizeof(nupath)-1);
		if ( rslt > 0 ) nupath[rslt] = '\0';
		else strcpy(nupath,"readlink error");
		printf(" -> %s", nupath);
	}
	printf("\n");
}

/**
 * processFileCallback - process one found directory entry
 *
 */
void processFileCallback(const char *name, const char *fullPath, const struct stat *statDat)
{
	if ( filenameMatches(name) )  {
		/* this will check for matches on dirs .. */
		printMatchingEntry(name,fullPath,statDat);
		pthread_mutex_lock( &config.configMutex );
		config.totalCount++;
		pthread_mutex_unlock( &config.configMutex );
	}
	/**
	 * Here is where it gets interesting because it may be a directory.
	 * TODO: make sure it's not a symlink - we will NOT process dir links
	 */
	if ( S_ISDIR(statDat->st_mode) ) {
		if ( strcmp(name,".") == 0 || strcmp(name,"..") == 0 )
			return;
		mtf_recurseDir(fullPath);
	}
}


/**
 * modebits
 *
 * return a string representation of a set of 3 mode bits,
 *   "rwx" and so forth.  Uses a static buffer which is
 *   overwritten with each call.
 *
 *   @param mode - an int with mode bits in the ls 3 bits corresponding to r, w, and x
 *   @return - pointer to string
 */
static
char *modebits( int mode )
{
	static char modestr[4];

	if ( mode & 4 )
		modestr[0] = 'r';
	else modestr[0] = '-';
	if ( mode & 2 )
		modestr[1] = 'w';
	else modestr[1] = '-';
	if ( mode & 1 )
		modestr[2] = 'x';
	else modestr[2] = '-';

	modestr[3] = '\0';
	return modestr;
}

/**
 * modestring	-	interpret the mode bits and make a string of them all
 *
 * @param - mode, from stat mode field
 * @param - str, output string buffer, guaranteed to be long enough
 * 			which we will define as 16 for now
 *
 */

static
void modestring( int mode, char *str )
{
	char type;

	if ( S_ISDIR(mode) ) type = 'd';
	else if ( S_ISCHR(mode) ) type = 'c';
	else if ( S_ISBLK(mode) ) type = 'b';
	else if ( S_ISREG(mode) ) type = '-';
	else if ( S_ISFIFO(mode) ) type = 'p';	// pipe
	else if ( S_ISSOCK(mode) ) type = 'k';	// pipe
	else if ( S_ISLNK(mode) ) type = 'l';
	else type = '-';

	*str++ = type;

	if (  mode & S_ISUID )
		*str++ = 's';
	else *str++ = ' ';

	if ( mode & S_ISVTX )
		*str++ = 's';
	else *str++ = ' ';
	*str++ = ' ';
	strcpy( str, modebits( (mode >> 6) & 7 ) );
	strcpy( str+3, modebits( (mode >> 3) & 7 ) );
	strcpy( str+6, modebits( mode  & 7 ) );

}
