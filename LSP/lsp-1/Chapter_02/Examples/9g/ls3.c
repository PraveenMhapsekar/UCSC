// sourced from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Stat/lecture.html

// read filenames from current directory; and; print filename & size
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

int main()
{
  struct stat buf;
  int exists;
  DIR *d;
  struct dirent *de;

  d = opendir(".");
  if (d == NULL) {
    fprintf(stderr, "Couldn't open \".\"\n");
    exit(1);
  }

  // for (de = readdir(d); de != NULL; de = readdir(d)) {

  de = readdir(d); 
  while (de != NULL) {
    exists = stat(de->d_name, &buf);

    if (exists < 0) 
      fprintf(stderr, "%s not found\n", de->d_name);
    else 
      printf("%s %ld\n", de->d_name, buf.st_size);
   
  	de = readdir(d); 
  }

	closedir(d);
	return 0;
}

