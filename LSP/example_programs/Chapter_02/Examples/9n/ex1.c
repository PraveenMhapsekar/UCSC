// chdir() to <dir> ..  command line argument
// realpath()

// sourced/adapted from http://linux.die.net/man/3/stat

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

extern char *get_dirname(char *dn);
extern int process_ls(char *dn);
extern int print_oneline(struct stat *statbufptr);
extern char *get_modebits(mode_t,char *);

struct dirent  *dp;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char            datestring[256];
DIR	*dir;

int main(int argc, char **argv) {

	char dn[500];
	char rp[500];

  strcpy(dn, (argc==2)? argv[1]: ".");
	
	if (realpath(dn,rp)) {

		// navigate to that directory.
		if (chdir(rp)) {
			if (chdir(get_dirname(rp))) {
				fprintf(stderr,"%s:%s\n",rp,strerror(errno));		
				return 0;
			}
		}

		fprintf(stderr, "Opening dir=\"%s\"\n",rp);
	}
	else {
		fprintf(stderr, "Error Opening dir=\"%s\"\n",rp);
		return 0;
	}
		
 	process_ls(rp);

	return 0;

}

char *get_dirname(char *dn) {

	// http://www.koders.com/c/fid39D4F91CC907BFAFB5AB19B1106F8F07A014A990.aspx

	char *s;
	s=dn+strlen(dn)-1;

	// strip out multiple trailing slashes, if any
	while (s && *s == '/') {		
		*s = '\0';
		s=dn+strlen(dn)-1;
	}

	s = strrchr(dn, '/');
	if (s && *s)
		*s = '\0';

	// printf("%s\n", (s)? dn : ".");
	return(s);
}


int process_ls(char *dn) {

	struct stat     statbuf;

	if ((dir=opendir(dn))==NULL) {
		fprintf(stderr, "Couldn't open dir=\"%s\"\n",dn);
		return 0;
	}

	/* Loop through directory entries. */
	while ((dp = readdir(dir)) != NULL) {

    /* Get entry's information. */
    if (lstat(dp->d_name, &statbuf) == -1) {
				fprintf(stderr, "Couldn't lstat entry=\"%s\"(%s)\n",dp->d_name,
				strerror(errno));
        continue;
		}

		print_oneline(&statbuf);
	}
	closedir(dir);

	return 0;
}

int print_oneline(struct stat     *statbufptr) {

	struct stat statbuf=*statbufptr;
	char buf[10];

    /* Print out type, permissions, and number of links. */
    printf("%10.10s", get_modebits((mode_t)statbuf.st_mode,buf));
    printf("%4d", statbuf.st_nlink);

    /* Print out owner's name if it is found using getpwuid(). */
    if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
        printf(" %-8.8s", pwd->pw_name);
    else
        printf(" %-8d", statbuf.st_uid);

    /* Print out group name if it is found using getgrgid(). */
    if ((grp = getgrgid(statbuf.st_gid)) != NULL)
        printf(" %-8.8s", grp->gr_name);
    else
        printf(" %-8d", statbuf.st_gid);

    /* Print size of file. */
    printf(" %9jd", (intmax_t)statbuf.st_size);

    tm = localtime(&statbuf.st_mtime);

    /* Get localized date string. */
    strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

    printf(" %s %s\n", datestring, dp->d_name);
	
	return 0;
}

char *get_modebits(mode_t modebits,char *buf) {
		int i=0;
	
    if      (S_ISDIR(modebits))		buf[i]='d';
    else if (S_ISFIFO(modebits))	buf[i]='p';
    else if (S_ISLNK(modebits))		buf[i]='l';
    else if (S_ISBLK(modebits))		buf[i]='b';
    else if (S_ISCHR(modebits))		buf[i]='c';
    else if (S_ISSOCK(modebits)) 	buf[i]='s';
    else if (S_ISREG(modebits))		buf[i]='-';
		else 													buf[i]='!';

		i++;
		buf[i++]=(modebits & S_IRUSR) ?	'r' : '-';
		buf[i++]=(modebits & S_IWUSR) ?	'w' : '-';
		buf[i++]=(modebits & S_IXUSR) ?	'x' : '-';

		buf[i++]=(modebits & S_IRGRP) ?	'r' : '-';
		buf[i++]=(modebits & S_IWGRP) ?	'w' : '-';
		buf[i++]=(modebits & S_IXGRP) ?	'x' : '-';

		buf[i++]=(modebits & S_IROTH) ?	'r' : '-';
		buf[i++]=(modebits & S_IWOTH) ?	'w' : '-';
		buf[i++]=(modebits & S_IXOTH) ?	'x' : '-';

    return buf; 
}



