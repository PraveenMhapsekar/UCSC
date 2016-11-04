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

#ifdef _POSIX_SOURCE
#define SA_RESTART 0x000004
#endif

#define MYSERVER_DATA_FOUND "LineNumber Found"
#define  MYSERVER_UDP_PORT_NUMBER 29786

char *ProgramName="udp_client";
int InetAddressInit(struct sockaddr_in *saddr, char *hostname, 
	int portnum, char *errbuf);


int getUDPsocket(char *myhostname, int port_number, char *errbuf) {

	struct sockaddr_in dgram_addr[1];
	int		udp_sd;

	char	localbuf[256];

	int 	status;

	status=InetAddressInit(dgram_addr, myhostname, port_number, errbuf);

	if (status != 0) {
		sprintf(errbuf, "couldn't get inet address: %s", localbuf);
		return status;
	}

	udp_sd = socket(AF_INET, SOCK_DGRAM, PF_UNSPEC);

	if (udp_sd < 0) {
		sprintf(errbuf,"socket() error: %s\n",strerror(errno));
		return -1;
	}

	status=bind(udp_sd,(struct sockaddr *) dgram_addr, sizeof(struct sockaddr_in));

	if (status==-1) {
		sprintf(errbuf,"bind() error: port# %d: %s\n",port_number,strerror(errno));

		close(udp_sd);
		return -1;
	}

	return udp_sd;
}

int InetAddressInit(struct sockaddr_in *saddr, char *hostname, 
	int portnum, char *errbuf) {

	int nitems;
	int var;

	memset(saddr, 0, sizeof(struct sockaddr_in));

	saddr->sin_family = AF_INET;
	saddr->sin_port = htons((unsigned short)portnum);

	nitems = sscanf(hostname, "%*d.%*d.%*d.%d", &var);

	if (nitems == 1) {
		unsigned long addr;

		addr=inet_addr(hostname);

		memcpy (&(saddr->sin_addr), &addr, sizeof(struct in_addr));
	}
	else {

		struct hostent *hostinfo;

		hostinfo=gethostbyname(hostname);

		if (hostinfo == 0) {
			sprintf(errbuf,"gethostbyname() error: %s\n", strerror(errno));
		
			return -2;
		}

		if (hostinfo->h_addrtype != AF_INET) {
			sprintf(errbuf,"address type error: %s\n", strerror(errno));
		
			return -3;
		}

		memcpy (&(saddr->sin_addr), hostinfo->h_addr_list[0], sizeof(struct in_addr));

	}

	return 0;

}

int main(int argc,char **argv) {

	struct sockaddr_in	server_addr[1];
	struct sockaddr_in	reply_addr[1];

	char *myhostname="127.0.0.1";

	int	reply_addr_len;

	char *remote_host;
	int	sd, bytes_sent, flags;
	char *msgbuf;
	int	msglen, reply_length;
	char	rcvbuf[1024];	// receive buffer
	char	errbuf[1024];	// error buffer
	int	status;

	ProgramName=*argv;

	if (*argv == 0){
		fprintf(stderr, "Err: Need name of Remote Host as argument\n");
		exit(1);
	}

	// remote_host=*argv;

	remote_host=myhostname;
	sd=getUDPsocket(myhostname,0,errbuf);

	if (sd <0) {
		fprintf(stderr, "Err: Couldn't get UDP socket : %s\n", errbuf);
		exit(1);
	}

	status=InetAddressInit(server_addr, remote_host, MYSERVER_UDP_PORT_NUMBER, errbuf);

	if (status!=0) {
		fprintf(stderr, "Err: Couldn't get inet address : %s\n", errbuf);
		exit(1);
	}

	msgbuf="This is a test!";
	msglen=strlen(msgbuf);
	flags=0x0;

	bytes_sent=sendto(sd,msgbuf,msglen,flags,
		(struct sockaddr *) server_addr, sizeof(struct sockaddr_in));

	if (bytes_sent < msglen) {
		fprintf(stderr,"sendto() err: %s\n", 
			(bytes_sent < 0) ? strerror(errno) : "too few bytes");

		exit(1);
	
	}

	reply_addr_len = sizeof(reply_addr);

	reply_length = recvfrom(sd, rcvbuf, sizeof(rcvbuf), flags,
		(struct sockaddr *) reply_addr, &reply_addr_len);

	if (reply_length == -1) {
		fprintf(stderr,"recvfrom() err: %s\n", strerror(errno) );

		exit(1);
	}

	rcvbuf[reply_length] = 0;

	printf("\nReceived %d bytes from '%s':\n\t%s\n",
		reply_length, remote_host, rcvbuf);

	exit(0);
}
		
