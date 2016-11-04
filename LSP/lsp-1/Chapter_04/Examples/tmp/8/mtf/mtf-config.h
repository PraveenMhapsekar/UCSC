/*
 * mtf-config.h
 *
 *  Created on: Aug 3, 2010
 *      Author: Grgg Weissman
 *
 *  This file contains configuration info shared by the
 *  mt-find modules, gathered from the command line, rather
 *  than using globals.
 *
 */

#ifndef MTFCONFIG_H_
#define MTFCONFIG_H_

#include <pthread.h>

typedef struct {

	int	longFlag;
	/* TODO: maybe put a throttle on the # threads */
	int nThreads;

	/* search parameters */
	char *startPath;
	char *dfltFind;
	char **findList;
	int  nFinds;

	/* global config and synchronization state */
	int	threadsRunning;
	pthread_t topThread;

	/* only one mutex, protects total count and nThreads */
	pthread_mutex_t configMutex;

	/* total count of found files */
	int totalCount;

} s_mtfConfig;

#endif /* MTFCONFIG_H_ */
