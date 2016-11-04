/* ls5.c */

// sourced from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Stat/lecture.html

// print output similar to ls -F (plus, other types added .. for fun:-) )

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int mknod(const char *pathname, mode_t mode, dev_t dev);

#define MAXLINESIZE 80
#define MAXENTRYSIZE 14

  struct stat buf;
  int exists;
  DIR *d;
  struct dirent *de;
	char *str, *tmp;
	int count;

void print_inodeinfo(char *);

int main(int argc, char **argv)
{

	mknod("./myCHRDEV.dat",S_IFCHR|0660,makedev(32,0));
	mknod("./myBLKDEV.dat",S_IFBLK|0660,makedev(32,0));
	mknod("./mySOCKET.dat",S_IFSOCK|0660,0);

	str=malloc(MAXLINESIZE);
	tmp=malloc(MAXLINESIZE);
  d = opendir(".");
  if (d == NULL) {
    fprintf(stderr, "Couldn't open \".\"\n");
    exit(1);
  }
  
	printf(">>>>>>>>> Output of files in Current Directory <<<<<<<<<<<<\n");
  for (de = readdir(d); de != NULL; de = readdir(d)) {
    print_inodeinfo(de->d_name);
  }
	printf("%s\n",str);
	printf(">>>>>>>>>  End   <<<<<<<<<<<<\n");
  closedir(d);

	free(str);
	free(tmp);
	return 0;
}

void  print_inodeinfo(char *fn){
	  if ((strlen(str)+MAXENTRYSIZE+1)>=MAXLINESIZE){
			printf("%s\n",str);
		  str[0]=0;
	  }


    exists = lstat(fn, &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\t", fn);
    } else if (S_ISDIR(buf.st_mode)) {
      sprintf(tmp,"%14.14s/\t", fn);
      printf("ISDIR=%ld %#0x\n",buf.st_mode,buf.st_mode);
    } else if (S_ISFIFO(buf.st_mode)) {
      sprintf(tmp,"%14.14s|\t", fn);
      printf("ISFIFO=%ld %#0x\n",buf.st_mode,buf.st_mode);
    } else if (S_ISLNK(buf.st_mode)) {
      sprintf(tmp,"%14.14s@\t", fn);
      printf("ISLNK=%ld %#0x\n",buf.st_mode,buf.st_mode);
    } else if (S_ISBLK(buf.st_mode)) {
      sprintf(tmp,"%14.14s=\t", fn);
      printf("ISBLK=%ld %#0x\n",buf.st_mode,buf.st_mode);
    } else if (S_ISCHR(buf.st_mode)) {
      sprintf(tmp,"%14.14s^\t", fn);
      printf("ISCHR=%ld %#0x\n",buf.st_mode,buf.st_mode);
    } else if (S_ISSOCK(buf.st_mode)) {
      sprintf(tmp,"%14.14s>\t", fn);
      printf("ISSOCK=%ld %#0x\n",buf.st_mode,buf.st_mode);
    } else if (buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
      sprintf(tmp,"%14.14s*\t", fn);
    } else if (S_ISREG(buf.st_mode)) {
      sprintf(tmp,"%14.14s-\t", fn);
    } else {
      sprintf(tmp,"%14.14s\t", fn);
    }
		strcat(str,tmp);

		return;
}
