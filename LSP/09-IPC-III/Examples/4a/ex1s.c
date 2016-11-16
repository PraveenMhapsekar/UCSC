#include "ex1.h"

int init_server_connection(char *host, int port, struct sockaddr_in *);
int do_request(int csd, char *errbuf);
int process_request(int sd, struct sockaddr_in *, char *errbuf);

int do_select(int csd, char *errbuf);
int read_and_send(int csd, int rfd, char *errbuf);
int signal_handler(void);

void wait_child(int);

void wait_child(int sig) {
	while (waitpid(-1,0,WNOHANG) > 0);
}

int signal_handler(void) {

	struct sigaction new[1];
	struct sigaction old[1];

	sigemptyset(&new->sa_mask);
	new->sa_handler=wait_child;
	new->sa_flags=SA_RESTART;

	sigaction(SIGCHLD,new,old);
}

int process_request(int sd, struct sockaddr_in *from, char *errbuf) {
	
	int rc=0,csd;

	char str[256];

	unsigned int fromlen = sizeof(struct sockaddr_in);

	// wait for connection request from clients
	if ((csd=accept(sd, (struct sockaddr *)from, &fromlen)) < 0) {
		fprintf(stderr,"accept() error: %s\n", strerror(errno));
		return -1;
	}

	rc=do_request(csd, errbuf);
	return rc;
}

int do_request(int csd, char *errbuf) {

	int cpid=0, rfd=0;

	if ((cpid=fork()) < 0) {
		fprintf(stderr,"fork() error: %s\n", strerror(errno));
		return -1;
	}

	if (cpid==0) { 

		// child
		
		if ((rfd=open(MYSERVER_DATA_FILE, O_RDONLY)) < 0) {
			sprintf(errbuf,"File open error:%s:%s\n", 
				MYSERVER_DATA_FILE,strerror(errno));
			return -1;
		}

		while (do_select(csd, errbuf)) {
			errbuf[0]=0;

			if (read_and_send(csd,rfd,errbuf)< 0) {
				break;
			}
		}

		// no more data from client
		shutdown(csd,SHUT_RDWR);
		close(rfd);
		close(csd);

		_exit(0);
	}
	else {
		// parent
		close(csd);
		return 0;
	}
}
	
int do_select(int csd, char *errbuf) {

	fd_set	fdset;
	struct timeval tmout[1];

	int nrd=0, sd=csd;

	tmout->tv_sec=MYSERVER_SOCKET_READ_TIMEOUT;
	tmout->tv_usec=0;

	FD_ZERO(&fdset);

	FD_SET(sd,&fdset);

	if ((nrd=select(sd+1, &fdset,0,0,tmout)) < 0) {
		sprintf(errbuf,"select() failed: %s\n", strerror(errno));
		return 0;
	}
	else if (nrd==0) {
		sprintf(errbuf,"select() timed out\n");
		return 0;
	}

	if (FD_ISSET(sd, &fdset)) {
		return 1;
	}

	return 0;
}

int read_and_send(int csd,int rfd,char *errbuf) {

	Example ExampleData[1];

	char str[256];

	int i=0, j=0, rc=0, readpos=0, ExampleLineNum=0;

	str[0]=0;

	if (read(csd, str, sizeof(str)) < 0) {
		sprintf(errbuf, "Socket Read Error: %s\n", strerror(errno));
		return -1;
	}

	ExampleLineNum=atoi(str);
	readpos=(ExampleLineNum-1) * sizeof(Example);

 	// fprintf(stdout,"Server:Processing LineNum: %d:\n",ExampleLineNum);

	if (lseek(rfd, readpos, SEEK_SET) < 0) {
		sprintf(errbuf,"lseek() Error: %s\n", strerror(errno));
		return -1;
	}
	
	if ((i=(read(rfd, ExampleData, sizeof(struct Example)))) <= 0) {
		fprintf(stderr,"ERR: LineNum: %d: NOT FOUND\n", ExampleLineNum);
		sprintf(errbuf,"ERR: LineNum: %d: NOT FOUND\n", ExampleLineNum);
		strcpy (str,errbuf);
	}
	else {
		sprintf(str,"%s",MYSERVER_DATA_FOUND);
	}

	j=strlen(str)+1;
	if (write(csd,str,j)<j) {
		fprintf(stderr, "write() str Error: %s\n", strerror(errno));
		return -1;
	}
	
	j=sizeof(Example);
	if (i) {
    //fprintf(stderr,"\n\tLine Number\t: %d\n",ExampleData->linenum);
    //fprintf(stderr,"  \t\tData     \t: %s\n",ExampleData->data);
		sleep(1);
		if (write(csd,ExampleData,j)<j) {
			fprintf(stderr, "write() ExampleData Error: %s\n", strerror(errno));
			return -1;
		}
	}

	return 0;	
	
}

	
int main(int argc, char **argv) {

	int i=0,rc=0,cnt=0;

	int sd;

	// char *host="127.0.0.1"; "localhost";
	char *host=NULL;
	int port=MYSERVER_PORT_ADDRESS;

	char *srv="myserver";
	char *proto="tcp";

	char str[256];
	char errbuf[256];

	struct sockaddr_in sa_in[1];

	errbuf[0]=0;

	signal_handler();			// setup signal handler for exiting children

	if ((sd=init_server_connection(host,port,sa_in))<1) {
		fprintf(stderr,"init_server_connection() error: %s\n", strerror(errno));
		return -1;		
	}
	
	while (cnt++ < MYSERVER_CLIENTS) {
		if (rc=(process_request(sd, sa_in, errbuf))<0) {
			fprintf(stderr, "Request Processing Error: %s\n", errbuf);
			break;
		}
	}

	fprintf(stderr, "Reached Max. Sessions for Server\n", MYSERVER_CLIENTS);

	while (wait(0)>0) {
			fprintf(stderr, "Waiting for Sessions to Terminate.\n");
	}
	
	shutdown(sd,SHUT_RDWR);
  close(sd);

	return 0;
}
