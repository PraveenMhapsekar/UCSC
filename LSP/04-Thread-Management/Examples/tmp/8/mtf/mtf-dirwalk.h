/*
 * mtf-dirwalk.h
 *
 *  Created on: Aug 3, 2010
 *      Author: Gregg Weissman
 */

#ifndef MTFDIRWALK_H_
#define MTFDIRWALK_H_

/**
 * mtf_dirwalk -
 *
 * called from main to start the process of walking directories
 *
 * @return status from operations
 */
int mtf_dirwalk( void );

/**
 * mtf_recurseDir
 *
 * called when a directory entry is a directory to walk the new path.
 *
 * @param path - the path to recurse into, the caller is responsible for
 * not recursing into any cycles.
 */
void mtf_recurseDir(const char *path);

#endif /* MTFDIRWALK_H_ */
