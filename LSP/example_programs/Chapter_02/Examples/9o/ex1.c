
#define DIRBLKSIZ 256

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void);
static void ls(int);

int main(void) {
	struct stat st;
	int fd;

	if ((fd = open(".", 0)) == -1) exit(0);

	if (fstat(fd, &st) == -1) {
		printf("ls: cannot stat\n");
		return 0;
	}
	if (!S_ISDIR(st.st_mode)) {
		printf("ls: not a directory\n");
		return 0;
	}

	if (st.st_size == 0) {
		printf("ls: zero length directory\n");
		return 0;
	}
	ls(fd);
}

typedef struct dirent   DP;
static void ls(register int fd)
{
	register int size;
	register char *dp;
	char dirbuf[DIRBLKSIZ];

	printf("\ninode\tname\n");
	while ((size = read(fd, dirbuf, DIRBLKSIZ)) == DIRBLKSIZ)
		for (dp = dirbuf; (dp < (dirbuf + size)) &&
			(dp + ((DP *)dp)->d_reclen) < (dirbuf + size);
			dp += ((DP *)dp)->d_reclen) {

//					if (((DP *)dp)->d_fileno == 0) continue;

					printf("%d\t%s\n", ((DP *)dp)->d_fileno, ((DP *)dp)->d_name);
	}
}

