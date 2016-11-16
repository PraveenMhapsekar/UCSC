#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

int check_dirent(char *);

#define ISDIR(path) (stat(path,&sbuf)==-1)?0:S_ISDIR(sbuf.st_mode)

int main(int argc, char **argv) {
	if (argc == 2) check_dirent(argv[1]);
	else fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
	
	return 0;
}

int check_dirent(char *path) {
	struct dirent *dp;
  struct stat sbuf;
	DIR *dirp;
	
	if ((dirp = opendir(path)) == NULL) {
		fprintf(stderr,"%20.20s: %s\n", path, "Failed to open directory");
		return 1;
	}   
	
	while ((dp = readdir(dirp)) != NULL) {
		fprintf(stderr,"%-40.40s: %sdirectory.\n",dp->d_name,
			(ISDIR(dp->d_name)) ? "":"not a ");
	}
	
	closedir(dirp);
	
	return 0;
}
