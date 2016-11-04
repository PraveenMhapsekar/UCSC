// sourced from http://www.lainoox.com/find-mac-address/
#include <net/if.h>
#include<netinet/if_ether.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>     /* the L2 protocols */
#include <asm/types.h>
#include <linux/sockios.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define BUFSZ 512

/**
 * *  get_mac_str()
 * * interface_name        the name of the interface we want the MAC of
 * * mac_str               the buffer we will store the result in
 * * RETURNS: 0 on success; -1 on error.
 * */
int get_mac_str(const char *interface_name, char *mac_str) 
{
	int ioctl_data = 0;
 	struct ifreq ifr;
 
	// If either pointer is NULL
 	// if (!ifName || !macAddrStr) return(-1);
 	if (!interface_name) return(-1);
	
	// Setup our socket 
	if ( (ioctl_data = socket(PF_INET, SOCK_STREAM, 0)) == -1 ){
		fprintf(stderr, "Could not setup socket.\n");
		return(-1);
	}
        
	// Clear the IFREQ structure
	memset(&ifr, 0, sizeof(ifr));
	
	// Store our interface name in the structure for lookup
	strncpy(ifr.ifr_name, interface_name, sizeof(ifr.ifr_name));

	if ( ioctl(ioctl_data, SIOCGIFHWADDR, &ifr) < 0) {
 		fprintf(stderr, "Could not execute ioctl call.\n");
		close(ioctl_data);
		return(-1);
	}
	close(ioctl_data);
        
	// Ensure we are dealing with an Ethernet device
	if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) 
	{
		fprintf(stderr, "Not an ethernet device.\n");
		return(-1);
	}
	// C function to convert address to octet colon form
	ether_ntoa_r((const struct ether_addr *)&(ifr.ifr_hwaddr.sa_data), mac_str);
	return(0);
}

int main(int argc, char **argv) {
	char *buf;

	buf=malloc(BUFSZ);
	if (argc==2) {
		if (get_mac_str(argv[1],buf)!=-1) 
			fprintf(stderr,"MAC address=> %s",buf); 
		else return -1;
	}
	else
		fprintf(stderr,"Usage: $0 <interface name>\n");

	return 0;
}
