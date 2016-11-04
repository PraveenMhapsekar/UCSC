#include <stdio.h>
#include <fcntl.h>

int main() {

	char *wfn="/tmp/ch2/largefile2.dat";
	char buf[200000]={ ' ' };
	int fd=0, n=0, c=0;

		fd=open(wfn,O_WRONLY|O_CREAT|O_TRUNC,0660);

		buf[200000-1]=0;

		for (n=0; n++<6000;) 
			write(fd,buf,sizeof(buf));

		close(fd);

		fd=open(wfn,O_RDONLY);

		n=read(fd,buf,1);

		fprintf(stderr,"Done Reading\n");
		// c=getchar();

		close(fd);
}
