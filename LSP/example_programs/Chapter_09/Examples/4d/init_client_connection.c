#include "ex1.h"

int init_client_connection(char *host,int port, struct sockaddr_in *sa_in);

int init_client_connection(char *host,int port, struct sockaddr_in *sa_in) {

	struct addrinfo hints;
	struct addrinfo *result, *rp;

	int sd,i,rc=0;
	char portstr[1024];

	sprintf(portstr,"%d",port);

	memset(&hints, 0, sizeof(struct addrinfo));
 	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
 	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

  if((rc = getaddrinfo(host, portstr, &hints, &result))!=0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
 		exit(EXIT_FAILURE);
  }

	for (rp = result; rp != NULL; rp = rp->ai_next) {
 		if ((sd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol))==-1)
			continue;

		if (connect(sd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;                  /* Success */

		close(sd);
  }

	if (rp == NULL) {               /* No address succeeded */
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	return sd;
}
