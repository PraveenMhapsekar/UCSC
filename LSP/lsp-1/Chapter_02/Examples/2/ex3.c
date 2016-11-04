// ch2_2.c

#include <stdio.h>
#include <fcntl.h>

char *rfn= "myfile.txt";

int main() {
	int fd;
  char buf[20];
  int len=4;
	fd=open(rfn, O_RDONLY);
	
	write(fd,buf,len);

}
