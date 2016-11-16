#define MAXNUMTHREADS 1024
#define BUFSZ 128

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

#include <semaphore.h>

/*
	The fnmatch() function checks whether the string argument 
	matches the pattern argument, which is a shell wildcard pattern. 

  int sem_init(sem_t *sem, int pshared, unsigned int value); 
  The sem_init() function is used to initialize the semaphore's value. The pshared argument must be 0 for semaphores local to a process. 

*/

void *check_dirent(void *);
char *srchflnm;

#define ISDIR(fn) (lstat(fn,&sbuf)==-1)?0:S_ISDIR(sbuf.st_mode)

struct thread_info {    // thread control block 
	int				currThread;	// curr thread number, used to track array refs 
  pthread_t tid;       // ID returned by pthread_create() 
  int       thread_rc;  // rc from pthread_create 
  char      *pathname; 	// track curr path for each thread
};

sem_t sem;

pthread_attr_t attr;

int main(int argc, char **argv) {

	int i=-1;
	int rc=0;
	int thisThread=0;

	struct thread_info *tinfo;

	if (argc == argc) {
    sem_init(&sem,0,1); // sem_init(&sem,0,MAXNUMTHREADS);

		rc=pthread_attr_init(&attr);			// init
		// pthread_attr_setschedpolicy(&attr, SCHED_RR); // init & set
		tinfo=(struct thread_info *) 
				malloc(sizeof(struct thread_info)*MAXNUMTHREADS); // init
		srchflnm=argv[2];		// init
		thisThread=0;				// init
		for(i=0;i<MAXNUMTHREADS;) tinfo[i++].tid=0; // init

		tinfo[thisThread].pathname=malloc(BUFSZ);	

		if (!realpath(argv[1],tinfo[thisThread].pathname)) return -1;
		tinfo[thisThread].currThread=thisThread;
		
		rc+=(int) check_dirent((void *)tinfo);

		fprintf(stderr,"Found %d Matches.\n",rc);
		for(i=0;i<MAXNUMTHREADS;) free(tinfo[i++].pathname); // unwind
		free(tinfo);	// unwind

		sem_destroy(&sem); // unwind
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

  sem_wait(&sem);

	// Sanity Check:  if there is a timing issue, check if TID matches.
	if(!pthread_equal(tinfo[thisThread].tid,tid))
		for(i=0;++i<MAXNUMTHREADS;) 
			if(tinfo[i].tid)
				if(pthread_equal(tinfo[i].tid,tid)) { thisThread=i; break; }

  sem_post(&sem);

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

    			sem_wait(&sem);
					newThread=++(tinfo->currThread);
    			sem_post(&sem);

					childThreads[newThread]++;
					tinfo[newThread].pathname=malloc(BUFSZ);	
					strcpy(tinfo[newThread].pathname,buf);

					tinfo[newThread].thread_rc=pthread_create(
						&(tinfo[newThread].tid),&attr,check_dirent,(void *)tinfo);
					chdir(tinfo[thisThread].pathname);	// use path for thisThread
				}
				// free(svpath);
			}
			free(buf);
	}

	for(i=0;i<MAXNUMTHREADS;i++) {
		if (childThreads[i]) {
			pthread_join(tinfo[i].tid,(void **)(int *)&(tinfo[i].thread_rc));
			rc+=(int)tinfo[i].thread_rc;
		}
	}
	closedir(dirp);

	return (int *)rc;
}
