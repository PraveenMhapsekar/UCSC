// http://www.lainoox.com/get-interface-index-c/
// Headers needed
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
 
int get_interface_index(const char *interface_name)
{
      struct ifreq ifr;
      int fd;
 
      memset(&ifr, 0, sizeof(ifr));
 
      // setup ifr for ioctl 
      strncpy (ifr.ifr_name, interface_name, sizeof(ifr.ifr_name) - 1);
      ifr.ifr_name[sizeof(ifr.ifr_name)-1] = '\0';
 
      // create socket
      fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
      if ( fd == -1) {
             fprintf(stderr," Could not create raw socket:  %s \n", strerror(errno));
             return -1;
      }
 
      // get index 
      if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1)
      {
              close(fd);
              return (-1);
      }
      // close socket if created locally
      close(fd);
 
      return ifr.ifr_ifindex;
}

int main(int argc, char **argv) {
	char *buf;

	if (argc==2) {
			fprintf(stderr,"Interface Index=> %d",get_interface_index(argv[1]));
	}
	else
		fprintf(stderr,"Usage: $0 <interface name>\n");

	return 0;
}
