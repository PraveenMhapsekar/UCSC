// sourced from http://www.lainoox.com/set-ip-address-c-linux/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <errno.h>
#include <netinet/in.h>
#if defined(__GLIBC__) && __GLIBC__ >=2 && __GLIBC_MINOR__ >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>
#else
#include <sys/types.h>
#include <netinet/if_ether.h>
#endif
 
int set_ip(char *iface_name, char *ip_addr)
{
	if(!iface_name)
		return -1;	
 
	int sockfd;
	struct ifreq ifr;
	struct sockaddr_in sin;
 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1){
		fprintf(stderr, "Could not get socket.\n");
		return -1;
	}
 
	/* get interface name */
	strncpy(ifr.ifr_name, iface_name, IFNAMSIZ);
 
	/* Read interface flags */
	if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
		fprintf(stderr, "ifdown: shutdown ");
		perror(ifr.ifr_name);
		return -1;
	}
 
	/*
	* Expected in <net/if.h> according to
	* "UNIX Network Programming".
	*/
	#ifdef ifr_flags
	# define IRFFLAGS       ifr_flags
	#else   /* Present on kFreeBSD */
	# define IRFFLAGS       ifr_flagshigh
	#endif
 
	// If interface is down, bring it up
	if (ifr.IRFFLAGS | ~(IFF_UP)) {
		fprintf(stdout, "Device is currently down..setting up.-- %u\n",ifr.IRFFLAGS);
		ifr.IRFFLAGS |= IFF_UP;
		if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0) {
			fprintf(stderr, "ifup: failed ");
			perror(ifr.ifr_name);
			return -1;
		}
	}
 
	sin.sin_family = AF_INET;
 
	// Convert IP from numbers and dots to binary notation
	inet_aton(ip_addr,&sin.sin_addr.s_addr);	
	memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr));	
 
	// Set interface address
	if (ioctl(sockfd, SIOCSIFADDR, &ifr) < 0) {
		fprintf(stderr, "Cannot set IP address. ");
		perror(ifr.ifr_name);
		return -1;
	}	
	#undef IRFFLAGS		
 
	return 0;
}
 
void usage()
{
	const char *usage = {
		"./set_ip [interface] [ip address]\n"
	};
	fprintf(stderr,"%s",usage);
}
 
int main(int argc, char **argv)
{
	if(argc < 3){
		usage();
		return -1;
	}
 
	set_ip(argv[1],argv[2]);
 
	return 0;
}
