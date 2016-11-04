/*
 * mtf_dirwalk.c
 *
 *  Created on: Aug 3, 2010
 *      Author: Gregg Weissman
 *
 *  Module of multi-threaded find, this drives the
 *  iteration over the specified directory/ies, issuing
 *  a callback for each entry found.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "mtf-config.h"
#include "mtf-direntry.h"

extern s_mtfConfig config;

/**
 * static helper functions
 *
 */
static
void spawnNewDirwalker(const char *path);
static
void *newDirwalkThread(void *arg);

/**
 * processDirectory
 *
 * @param path - name of directory
 *
 */
void processDirectory( const char *path )
{
	char *fullPathDup;
	int fnameMaxLen;
	char *pathEnd;
	DIR *dirp;
	struct dirent *dep;
	struct stat statDat;

	dirp = opendir(path);
	if ( dirp == NULL ) {
		fprintf(stderr,"Unable to open %s directory\n",path);
		return;
	}

	/**
	 * create a buffer known to be large enough for the
	 * path and any filenames
	 */
	fnameMaxLen = pathconf(path,_PC_NAME_MAX);
	if ( fnameMaxLen == -1 ) {
		fprintf(stderr,"Unable to get _PC_NAME_MAX in %s directory\n",path);
		return;
	}
	fullPathDup = (char *)malloc( strlen(path) + fnameMaxLen + 4);
	/* this is all inefficient! */
	strcpy(fullPathDup,path);
	if ( (strlen(fullPathDup) > 0) && (fullPathDup[strlen(fullPathDup)-1] != '/')  ){
		strcat(fullPathDup,"/");
	}
	pathEnd = fullPathDup + strlen(fullPathDup);
	/*printf("Directory listing for: %s\n",path);*/
	while ( (dep = readdir(dirp)) != NULL ) {
		strcpy(pathEnd,dep->d_name);
		stat(fullPathDup,&statDat);
		processFileCallback(dep->d_name,fullPathDup,&statDat);
	}
	closedir(dirp);
	free(fullPathDup);
}


/**
 * mtf_dirwalk - initial entry point to walk the path
 */
int mtf_dirwalk( void )
{
	char *canonicalPath;

	canonicalPath = realpath(config.startPath,NULL);
	if ( canonicalPath == NULL ) {
		fprintf(stderr,"realpath failed on %s\n",config.startPath);
		return(-1);
	}
#if DEBUG
	printf("Canonical path: %s\n",canonicalPath);
#endif
	processDirectory( canonicalPath );
	free(canonicalPath);
	return(0);
}

/**
 * mtf_recurseDir - entry point to recurse the walk
 *
 * @param path - the full path to start walking.
 */
void mtf_recurseDir(const char *path)
{

#if DEBUG
	printf("recursing into: %s\n",path);
#endif

	/* see if we are to spawn a new thread */
	if ( pthread_equal(config.topThread,pthread_self()) ) {
		spawnNewDirwalker(path);
	} else processDirectory(path);
}

/**
 * spawnNewDirwalker - helper function to encapsulate the start and stop
 * of a thread to recurse the tree from the current path.
 */
static
void spawnNewDirwalker(const char *path)
{
	pthread_t 	newThread;
	pthread_attr_t threadAttrs;
	int			rslt;
	char		*newPath;

	/* this messed me up at first: make sure to copy the path! */
	newPath = strdup(path);
	if ( newPath == NULL ) {
		fprintf(stderr,"fatal memory error\n");
		exit(-1);
	}
	/* TODO: handle errors! */
	rslt = pthread_attr_init( &threadAttrs );
	rslt = pthread_attr_setdetachstate(&threadAttrs,PTHREAD_CREATE_DETACHED);

	/* inc the thread count, and this has to be synchronized */
	/* I sync the new thread so the print can complete correctly */
	rslt = pthread_mutex_lock( &config.configMutex );
	rslt = pthread_create(&newThread,&threadAttrs,newDirwalkThread,(void*)newPath);
	config.threadsRunning++;
#if DEBUG
	printf("new thread created (count %d) :%x\n",config.threadsRunning,newThread);
#endif
	rslt = pthread_mutex_unlock( &config.configMutex );
}

/**
 * newDirwalkThread - another helper which wraps the start of the new thread
 * and the thread counter
 */
static
void *newDirwalkThread(void *arg)
{
	const char *path = (const char *)arg;
	int rslt;

	rslt = pthread_mutex_lock( &config.configMutex );
	rslt = pthread_mutex_unlock( &config.configMutex );

	processDirectory(path);
	/* now that the directory processing is done, terminate the thread */
	rslt = pthread_mutex_lock( &config.configMutex );
	/* TODO: handle errors! */
	config.threadsRunning--;
	rslt = pthread_mutex_unlock( &config.configMutex );
	/* the path was created for this thread and has to be destroyed */
	// free(path);
	/* ends the thread */
	return(NULL);
}
