// ch2_18.c
// using lstat() instead of stat

/*
******* excerpted from man page  *********

The lstat() function is like stat() except in the case where the named
file is a symbolic link; lstat() returns information about the link,
while stat() returns information about the file the link references.

Unlike other filesystem objects, symbolic links may not have an owner,
group, access mode, times, etc.  Instead, these attributes may be taken
from the directory that contains the link.  In this case, the only
attributes returned from an lstat() that refer to the symbolic link
itself are the file type (S_IFLNK), size, blocks, and link count (always
1).

*/


#define _POSIX_SOURCE 1

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>

#include <sys/stat.h>

char *rfn= "myfile.txt";

extern void print_statinfo(struct stat *statinfo);

int main(int argc, char **argv) {

	struct stat statinfo;
	char fn[1024];

	fprintf(stderr, "Enter File Name(or, EOF (ctrl-D) to exit):");

	if (gets(fn)) {

		if(lstat(fn, &statinfo) != 0) {
			fprintf(stderr, "stat() failed: %s\n", strerror(errno));
		}
		else {
			fprintf(stderr, "stat() info: %s\n", fn); 
			print_statinfo(&statinfo);
		}
		// fprintf(stderr, "Enter File Name(or, EOF (ctrl-D) to exit):");

	}
	exit(0);
}

void print_statinfo(struct stat *statinfo) {

	printf("\tino_t  st_ino\t==%-10lu\n", statinfo->st_ino);
	printf("\tmode_t st_mode\t==\t%07o\n", statinfo->st_mode);
	printf("\toff_t  st_size\t==%-10lu\n", statinfo->st_size);
	printf("\ttime_t st_atime\t==%10d\n", statinfo->st_atime);
	printf("\ttime_t st_mtime\t==%10d \n", statinfo->st_mtime);
	printf("\ttime_t st_ctime\t==%10d \n", statinfo->st_ctime);
	printf("\tlong   st_blksize\t==%9ld\n", statinfo->st_blksize);
	printf("\tlong   st_blocks\t==%9ld\n", statinfo->st_blocks);

}
