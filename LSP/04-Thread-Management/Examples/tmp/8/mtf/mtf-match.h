/*
 * mtf-match.h
 *
 *  Created on: Aug 8, 2010
 *      Author: Gregg Weissman
 *      Linux systems programming
 *
 *  Calls the pcre api to determine a match on a filename
 */

#ifndef MTFMATCH_H_
#define MTFMATCH_H_

#include <stdbool.h>

/**
 * filenameMatches - compare a filename against the search strings
 *
 * @param name - the found filename to match against user's reg exp
 * @return - true if match, false if not
 */
bool filenameMatches(const char *name);

/**
 * initRegexps - allocate and compile user's search string reg exps
 *
 * @return - < 0 if error occurs
 */
int initRegexps(void);

/**
 * destroyRegexps - release the resources of the compiled reg exps
 *
 */
void destroyRegexps(void);

#endif /* MTFMATCH_H_ */
