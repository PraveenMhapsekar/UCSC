/*
 * mtf-direntry.h
 *
 *  Created on: Aug 3, 2010
 *      Author: root
 */

#ifndef MTFDIRENTRY_H_
#define MTFDIRENTRY_H_

/* these are requisites for the declaration */
#include <sys/stat.h>
#include <sys/types.h>

void processFileCallback(const char *name, const char *fullPath, const struct stat *statDat);

#endif /* MTFDIRENTRY_H_ */
