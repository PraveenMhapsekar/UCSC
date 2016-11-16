#include "ex1.h"

int init_client_connection(char *host, int port,struct sockaddr_in *sa_in);

int init_client_connection(char *host, int port,struct sockaddr_in *sa_in) {

  struct hostent *hp;
	int sd,i,rc=0;

	// open a socket
	if ((sd=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		fprintf(stderr,"Socket Open Failure: %s\n", strerror(errno));
		return -1;
	}

	if (host)
  	// get IP address on Server NIC
  	if ((hp=gethostbyname(host))==NULL) {
    	fprintf(stderr,"host name lookup failure: %s\n", strerror(errno));
    	return -1;
  	}


	// get into Network Independent Format ..  htons() htonl()
  memset(sa_in,0,sizeof(*sa_in));
  sa_in->sin_family=AF_INET;
  sa_in->sin_port=htons(MYSERVER_PORT_ADDRESS);
	sa_in->sin_addr.s_addr=(*((unsigned long *) hp->h_addr_list[0]));
	fprintf(stderr, "IP Address: %s\n", inet_ntoa(sa_in->sin_addr));
	
	// connect()
	if (connect(sd,(struct sockaddr *)sa_in,sizeof(*sa_in)) < 0) {
		fprintf(stderr,"connect() failure: %s\n", strerror(errno));
		return -1;
	}
	return sd;
}
