// #define MAXNUMTHREADS 256
 
// #define MAXNUMTHREADS 1024
#define MAXNUMTHREADS 1024
// #define BUFSZ 192
#define BUFSZ 512

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fnmatch.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>

/*
	The fnmatch() function checks whether the string argument 
	matches the pattern argument, which is a shell wildcard pattern. 
*/

void *check_dirent(void *);
char *srchflnm;

#define ISDIR(fn) (lstat(fn,&sbuf)==-1)?0:S_ISDIR(sbuf.st_mode)

struct thread_info {    // thread control block 
	int				currThread;	// curr thread number, used to track array refs 
  pthread_t *tid;       // ID returned by pthread_create() 
  int       thread_rc;  // rc from pthread_create 
  char      *pathname; 	// track curr path for each thread
};

pthread_attr_t attr;

int main(int argc, char **argv) {

	int i=-1;
	int rc=0;
	int thisThread=0;

	struct thread_info *tinfo;

	if (argc == argc) {
		rc=pthread_attr_init(&attr);			// init
		// pthread_attr_setschedpolicy(&attr, SCHED_RR); // init & set
		tinfo=(struct thread_info *) 
				malloc(sizeof(struct thread_info)*MAXNUMTHREADS);
		srchflnm=argv[2];		// init
		thisThread=0;				// init
		for(i=0;i<MAXNUMTHREADS;) tinfo[i++].tid=NULL; // init

		tinfo[thisThread].tid=(pthread_t *)malloc(sizeof(pthread_t));	
		tinfo[thisThread].pathname=malloc(BUFSZ);	

		realpath(argv[1],tinfo[thisThread].pathname);
		tinfo[thisThread].currThread=thisThread;
		
		rc+=(int) check_dirent((void *)tinfo);

		fprintf(stderr,"Found %d Matches.\n",rc);
		for(i=0;i<MAXNUMTHREADS;) free(tinfo[i++].tid); // init
		for(i=0;i<MAXNUMTHREADS;) free(tinfo[i++].pathname); // unwind
		free(tinfo);	// unwind
	}
	else 
		fprintf(stderr,"Usage(%d): %s directory_name search_filename\n", 
			argc,argv[0]);
	
	return 0;
}

void *check_dirent(void *arg) {

	struct thread_info *tinfo = (struct thread_info *) arg;

	struct dirent *dp;
  struct stat sbuf;
	DIR *dirp;

	int	i;
	int	isdir=0;
	int rc=0;
	int thisThread;
	int newThread=0;
	int childThreads[MAXNUMTHREADS];

	char *path;
	char *buf;

	pthread_t tid=pthread_self();		// init

	thisThread=tinfo->currThread;		// init

	// Sanity Check:  if there is a timing issue, check if TID matches.
	if(!pthread_equal(*tinfo[thisThread].tid,tid))
		for(i=0;++i<MAXNUMTHREADS;) 
			if(tinfo[i].tid)
				if(pthread_equal(*tinfo[i].tid,tid)) { thisThread=i; break; }

	newThread=thisThread; 	// initialize for future reference.

	path=tinfo[thisThread].pathname;	// init

	for (i=0;i<MAXNUMTHREADS;) childThreads[i++]=0; // init

	if ((dirp = opendir(path)) == NULL) {		// start traversal & checks
		fprintf(stderr,"%50.50s: %s\n",path, "diropen Failed.");
		return 0;
	}   

	// key premise of this section 
	//  .. stat() works on valid path entries, 
	//  .. therefore chdir() as needed.
	while ((dp = readdir(dirp)) != NULL) {

			if ((!strcmp(".",dp->d_name)) || (!strcmp("..",dp->d_name))) 
				continue;

			buf=(char *)malloc(BUFSZ);

			{
				char *tmpbuf=(char *)malloc(BUFSZ);
				sprintf(tmpbuf,"%s/%s",path,dp->d_name);
				realpath(tmpbuf,buf);
				free(tmpbuf);
			}

			isdir=ISDIR(buf);

			if (!(fnmatch(srchflnm,dp->d_name,FNM_PATHNAME))) {
				fprintf(stderr,"Found(%d): %s\n",thisThread,buf);
				rc++;
			}

			if (isdir) {
				// char *svpath; 
				// svpath=(char *)malloc(BUFSZ);
				// getcwd(svpath,sizeof(svpath));	// save full path for now

				chdir(buf);								 		// use full path

				if (thisThread+1 < MAXNUMTHREADS) {
					newThread=++(tinfo->currThread);
					childThreads[newThread]++;
					if (!tinfo[newThread].tid)
						tinfo[newThread].tid=(pthread_t *)malloc(sizeof(pthread_t));	
					tinfo[newThread].pathname=malloc(BUFSZ);	
					strcpy(tinfo[newThread].pathname,buf);

					tinfo[newThread].thread_rc=pthread_create(
						(tinfo[newThread].tid),&attr,check_dirent,(void *)tinfo);
					chdir(tinfo[thisThread].pathname);	// use path for thisThread
				}
				// free(svpath);
			}
			free(buf);
	}

	for(i=0;i<MAXNUMTHREADS;i++) {
		if (childThreads[i]) {
			pthread_join(*tinfo[i].tid,(void **)(int *)&(tinfo[i].thread_rc));
			rc+=(int)tinfo[i].thread_rc;
		}
	}
	closedir(dirp);

	return (int *)rc;
}
