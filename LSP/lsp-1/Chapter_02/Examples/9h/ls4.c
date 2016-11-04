// sourced from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Stat/lecture.html

// similar to previous example, except that some formatting added
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

  struct stat buf;
  DIR *d;
  struct dirent *de;
  int maxlen;
  int exists;
	char *fn;

void print_inodeinfo(char *);

int main(int argc, char **argv)
{
  d = opendir(".");
  if (d == NULL) {
    fprintf(stderr, "Couldn't open \".\"\n");
    exit(1);
  }
  
  maxlen = 12;

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    if (strlen(de->d_name) > maxlen) maxlen = strlen(de->d_name);
    print_inodeinfo(de->d_name);
  }
  closedir(d);
}

void  print_inodeinfo(char * file) {
    exists = stat(file, &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\n", file);
    } else {
      printf("%*s %10ld\n", -maxlen, file, buf.st_size);
    }
  }

