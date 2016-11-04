//
// this example uses PCRE .. Perl-Compatible Regular Expression
// for Fedora   ..  yum -y install pcre
//          and,    yum -y install pcre-devel
// for Ubuntu   see http://cogo.wordpress.com/2010/07/19/pcre-h-no-such-file-or-directory-when-installing-apc-php-extension/
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pcre.h>

/*
	The fnmatch() function checks whether the string argument matches the pattern argument, which is a shell wildcard pattern. 
*/

int match(char *,char *);
int check_dirent(char *);
char *srchflnm;

#define ISDIR(fn) (lstat(fn,&sbuf)==-1)?0:S_ISDIR(sbuf.st_mode)

int main(int argc, char **argv) {
	if (argc == 3) {
			srchflnm=argv[2];
			check_dirent(argv[1]);
	}
	else fprintf(stderr, "Usage: %s directory_name search_filename\n", 
			argv[0]);
	
	return 0;
}

int check_dirent(char *path) {
	struct dirent *dp;
  struct stat sbuf;
	DIR *dirp;
	int	isdir=0;
	char svpath[1024]; // required on stack
	char buf[1024]; 	 // required on stack

	static char pathbuf[1024]; // not needed on stack.
	
	if ((dirp = opendir(path)) == NULL) {
		fprintf(stderr,"%30.30s: %s\n", path, "Failed to open directory");
		return 1;
	}   

	// key premise of this section 
	//  .. stat() works on valid path entries, 
	//  .. therefore chdir() as needed.
	while ((dp = readdir(dirp)) != NULL) {
			if ((!strcmp(".",dp->d_name)) || (!strcmp("..",dp->d_name))) 
				continue;

			sprintf(buf,"%s/%s",path,dp->d_name);
			isdir=ISDIR(buf);

			if ((match(srchflnm,dp->d_name))) {
				fprintf(stderr,"Found: %s\n",realpath(buf,pathbuf));
			}

			if (isdir) {
				getcwd(svpath,sizeof(svpath));	// save full path for now
				chdir(path);								 		// used path

				check_dirent(dp->d_name);
				chdir(svpath);								 	// used saved path from earlier
			}
	}
	
	closedir(dirp);
	
	return 0;
}

int match(char *srch, char *pattern) {

	const char *err;
	static pcre *re;
	static int rc;
	static int erroffset;
	int len=strlen(pattern);

	if((re=pcre_compile(srch,0,&err,&erroffset,NULL))==NULL) {
		fprintf(stderr,"regexp parse of %s failed because %s, at offs %d\n",srch,err,erroffset);
		return 0;
	}
	rc=pcre_exec(re,NULL,pattern,len,0,0,NULL,0);
	pcre_free(re);

	if (rc==0) return 1;
	return 0;
}
