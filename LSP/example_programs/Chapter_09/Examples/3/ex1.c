// adapted from http://gnosis.cx/publish/programming/sockets.html

#include <stdio.h>    
#include <stdlib.h>  

#include <netdb.h>    
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
	int i=0;
	struct hostent *h_e; 
	struct in_addr h_addr; 

	if (argc != 2) { 
		fprintf(stderr,"%s <fqdn/hostname/ipaddr>\n",argv[0]); return 0;
	}

	if ((h_e = gethostbyname(argv[1])) == NULL) {
		fprintf(stderr, "lookup failure '%s'\n", argv[1]);
		return 0;
	}

	// print first address only
	h_addr.s_addr = *((unsigned long *) h_e->h_addr_list[0]);
	fprintf(stderr, "1. IP Address: %s\n", inet_ntoa(h_addr));

/*
	// alternatively print all the IP Addresses got from DNS
	for(i=1;h_e->h_addr_list[i]!='\0';i++) {
            fprintf(stderr,"%d. IP Address: %s\n", i+1, 
							inet_ntoa(*((struct in_addr *)h_e->h_addr_list[i])));
  }
*/
	exit(0);
}
