/*
 * mtf-match.c
 *
 *  Created on: Aug 8, 2010
 *      Author: Gregg Weissman
 *      Linux systems programming
 *
 *  Calls the pcre reg exp library api to determine a match on a filename
 */

#include <stdio.h>
#include <string.h>
#include <pcre.h>
#include "mtf-match.h"
#include "mtf-config.h"

/* extern global config */
extern s_mtfConfig 	config;

/* static array of reg exps */
static
pcre **regExpArray;

/**
 * initRegexps - use the glbal find-list and init all the
 * reg exps used for matching.
 */
int initRegexps(void)
{
	int i;
	char *cp;
	const char *error;
	int	errorOffs;

	regExpArray = (pcre **)malloc(config.nFinds * sizeof(pcre*));
	if ( regExpArray == NULL ) {
		return(-1);
	}
	for(i=0;i<config.nFinds;i++){
		cp = config.findList[i];
		regExpArray[i] = pcre_compile(cp,0,&error,&errorOffs,NULL);
		if (regExpArray[i] == NULL) {
			fprintf(stderr,"regexp parse of %s failed because %s, at offs %d\n",cp,error,errorOffs);
			return(-2);
		}
	}
	return(0);
}

/**
 * destroyRegexps - destroy the created reg exps
 */
void destroyRegexps(void)
{
	int i;
	for(i=0;i<config.nFinds;i++){
		pcre_free(regExpArray[i]);
	}
	free( regExpArray );
}
/**
 * filenameMatches - match the incoming name against the regexps, and
 * exit with true on the first match, else return false.
 */
bool filenameMatches(const char *name)
{
	int len = strlen(name);
	int i;
	for(i=0;i<config.nFinds;i++){
#if DEBUGVERBOSE
		printf("Testing for match on %s\n",name);
#endif
		int rslt = pcre_exec(regExpArray[i],NULL,name,len,0,0,NULL,0);
		if ( rslt == 0 ) return true;
	}
	return false;
}
