#include "ex1.h"

int init_server_connection(char *hostname, struct sockaddr_in *sa_in);

int init_server_connection(char *hostname, struct sockaddr_in *sa_in) {
	
	int sd;

	// open a socket
	if ((sd=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		fprintf(stderr,"Socket Open Failure: %s\n", strerror(errno));
		return -1;
	}

	// get into Network Independent Format ..  htons() htonl() 
  memset(sa_in,0,sizeof(*sa_in));
  sa_in->sin_family=AF_INET;
  sa_in->sin_port=htons(MYSERVER_PORT_ADDRESS);
  sa_in->sin_addr.s_addr=htonl(INADDR_ANY);

	// Socket binding
	if ((bind(sd,(struct sockaddr *)sa_in,sizeof(*sa_in))) < 0) {
		fprintf(stderr,"bind() error: %s\n", strerror(errno));
		return -1;
	}

	// Setup for listening on port
	if (listen(sd,MYSERVER_CLIENTS) < 0) {
		fprintf(stderr,"listen() error: %s\n", strerror(errno));
		return -1;
	}

	return sd;
}
