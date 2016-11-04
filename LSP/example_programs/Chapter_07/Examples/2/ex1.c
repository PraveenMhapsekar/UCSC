#include <stdio.h>
#include <string.h>

int main() {

	char *str="Hello World";
	char buf[20];

	int fd[2];
	int rc,rcrd,rcwr;

	rc=pipe(fd);
	if (rc > -1) {
		fprintf(stderr, "read fd for pipe ==> %d\n", fd[0]);
		fprintf(stderr, "write fd for pipe ==> %d\n", fd[1]);
		rcwr=write(fd[1],str,strlen(str));
		rcrd=read(fd[0],buf,sizeof(buf));
	}	

	if (rcrd>0)
		buf[rcrd]=0;

	printf("Got \"%s\".\n",buf);

	return 0;
}
