// sourced from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Stat/lecture.html

// to demo use of stat call; and, print filesize
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  int i;
  struct stat buf;
  int exists;

  for (i = 1; i < argc; i++) {
    exists = stat(argv[i], &buf);
    if (exists < 0) {
      fprintf(stderr, "%s not found\n", argv[i]);
    } else {
      printf("%10ld %s\n", buf.st_size, argv[i]);
    }
  }

	return 0;
}

