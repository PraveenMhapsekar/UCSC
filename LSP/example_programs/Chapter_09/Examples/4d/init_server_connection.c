#include "ex1.h"

int init_server_connection(char *hostname, int port, struct sockaddr_in *sa_in);

int init_server_connection(char *hostname, int port, struct sockaddr_in *sa_in) {
	
	int sd;
	int rc=0;

  struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s; 

	char portstr[1024];

	sprintf(portstr,"%d",port);

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */ 
  hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL; 
  hints.ai_addr = NULL; 
  hints.ai_next = NULL; 

  rc = getaddrinfo(hostname,portstr,&hints,&result);
  if (rc != 0) { 
       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
       return -1;
   }

   /* getaddrinfo() returns a list of address structures.
      Try each address until we successfully bind(2).
      If socket(2) (or bind(2)) fails, we (close the socket
      and) try the next address. */

   for (rp = result; rp != NULL; rp = rp->ai_next) {
			if ((sd=(socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol)))==-1)
           continue;

			if (bind(sd, rp->ai_addr, rp->ai_addrlen) == 0) {
				if ((rc=(listen(sd,MYSERVER_CLIENTS)))<0) {
					fprintf(stderr,"listen() error:%s.\n",strerror(errno));
					return -1;
				}
        break;                  /* Success */
			}
       close(sd);
   }

   if (rp == NULL) {               /* No address succeeded */
       fprintf(stderr, "Could not bind:%s\n",strerror(errno));
       return -1;
   }

  freeaddrinfo(result);           /* No longer needed */

	bcopy(rp->ai_addr,sa_in,rp->ai_addrlen);

	return sd;
}
