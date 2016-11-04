#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int sd=0;

	sd=socket(AF_INET, SOCK_DGRAM,PF_INET);

	fprintf(stderr,"sd=%d\n",sd);
	shutdown(sd,2);
	close(sd);

	return 0;
}
