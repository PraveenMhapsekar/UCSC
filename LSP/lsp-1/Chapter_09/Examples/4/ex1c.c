#include "ex1.h"

int init_client_connection(char *host,int port,struct sockaddr_in *sa_in);
void ProcessCommand(char *combuf, int sd);
int ParseCommand(char *str, char **argv, int max_args);
int DoCommand(char **argv, int argc, int sd, char *errbuf);
int GetBinaryData(int linenum, int sd, char *errbuf);

char *ProgramName;

int init_client_connection(char *host,int port,struct sockaddr_in *sa_in) { 

	struct hostent *hp;
	int sd=0,i,rc=0;

	// open a socket
	if ((sd=(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))) < 0) {
		fprintf(stderr,"Socket Open Failure: %s\n", strerror(errno));
		return -1;
	}

	// get IP address on Server NIC
	if ((hp=gethostbyname(host))==NULL) {
		fprintf(stderr,"host name lookup failure: %s\n", strerror(errno));
		return -1;
	}

	// get into Network Independent Format ..  htons() htonl()
  memset(sa_in,0,sizeof(*sa_in));
  sa_in->sin_family=AF_INET;
  sa_in->sin_port=htons(port);
	sa_in->sin_addr.s_addr=(*((unsigned long *) hp->h_addr_list[0]));
	fprintf(stderr, "IP Address: %s\n", inet_ntoa(sa_in->sin_addr));
	
	// connect()
	if ((rc=(connect(sd,(struct sockaddr *)sa_in,sizeof(*sa_in)))) < 0) {
		fprintf(stderr,"connect() failure: %s(%d)\n", strerror(errno),rc);
		return -1;
	}
	return sd;
}

void ProcessCommand(char *combuf, int sd) {
	
	char *vbuf[256];
	int maxargs = sizeof(vbuf) / sizeof(char *);
	int numargs;

	numargs = ParseCommand(combuf, vbuf, maxargs);

	if (numargs==maxargs) {
		fprintf(stderr,"too many args\n");
	}
	else if (numargs) {
		int status;
		char errbuf[128];

		if ((status=DoCommand(vbuf,numargs,sd, errbuf))==-1) {
			fprintf(stderr,"input args error: %s\n", errbuf);
		}
	}

	{
		int i=0;
		while (i++<numargs) free(vbuf[i]); 	// free argument vector
	}
		
}

int DoCommand(char **argv, int argc, int sd, char *errbuf) {

	int status;

	if (strcasecmp(*argv,"print") == 0) {
	
		int linenum;

		for (++argv; *argv; argv++) {
			errbuf[0]=0;

			linenum=atoi(*argv);

			if (linenum) {
				fprintf(stderr, "Printing Line# %d:\n",linenum);
				status=GetBinaryData(linenum, sd, errbuf);

				if (*errbuf)	
					fprintf(stderr, errbuf);
		
				if (status==-1) 
					return -1;
			}
		}

		return 0;
	}
	else if ((strcasecmp(*argv,"quit") == 0) || (strcasecmp(*argv,"exit") == 0)) {
		exit(0);
	}
	else if (strcasecmp(*argv,"help") == 0) {
		fprintf(stderr, "\tprint Line# Line# ... \tprints line\n");
		fprintf(stderr, "\thelp              ... \tthis message\n");
		fprintf(stderr, "\t[quit|exit|^D]    ... \tquits program\n");

		return 0;
	}	
	
	sprintf(errbuf, "invalid command: %s", *argv);

	return -1;
}

int GetBinaryData(int linenum, int sd, char *errbuf) {

	// Example	ExampleData[1];
	Example	*ExampleData=(Example *)malloc(sizeof(Example));

	char str[256];

	int i,rc=0,flags,status;

	str[0]=0;

	sprintf(str,"%d", linenum);

	i=strlen(str);

	if (write(sd,str,i)<i) {
		fprintf(stderr,"write() Error: %s\n", strerror(errno));
		return -1;
	}

	if (i=(read(sd,str,sizeof(str))) < 0) {
		fprintf(stderr,"read() Error: %s\n", strerror(errno));
		return -1;
	}


	/*
		Protocol Note:
			Server Sends MYSERVER_DATA_FOUND initially, 
			followed by data.
	*/

	// no MYSERVER_DATA_FOUND message recd
	if (strncmp(str,MYSERVER_DATA_FOUND,sizeof(MYSERVER_DATA_FOUND)-1)) {
		sprintf(errbuf,"Line# %d:No Data Found.\n",linenum);

		/*  
			flush data in socket buffers.
		*/

		//	set to non-blocking read, and discard until read fails

		if ((flags=fcntl(sd,F_GETFL,0))==-1) {
			fprintf(stderr, "fcntl() getflags error: %s\n", strerror(errno));
		}
		else {
			flags |= O_NONBLOCK;
	
			if (fcntl(sd,F_SETFL,flags)> -1) {
			
				// consume until EOF
				while (read(sd,str, sizeof(str))>0);

				flags ^= O_NONBLOCK;
				fcntl(sd,F_SETFL,flags);
			}
		}

		return 0;
	}

	// we know data exists
	if ((rc=(read(sd, ExampleData, sizeof(Example))))<=0) {
		sprintf(errbuf,"read() error.Connection Lost!, %s\n", strerror(errno));
		return -1;
	}

	if (linenum==ExampleData->linenum) {
		fprintf(stderr,"\n\tLine Number: %d\n",	ExampleData->linenum);
		fprintf(stderr,"\tData     : %s\n",	ExampleData->data);
	}
	
	return 0;
}
			
int ParseCommand(char *str, char **argv, int max_args) {

	int i=0, len=0;

	char *s=str;

	for (;*str;str++,len++) {
		if (isspace(*str)) {
			char *narg;

			narg=malloc(len+1);
			strncpy(narg,s,len);
			narg[len]=0;

			argv[i++]=narg;

			// consume multiple spaces
			for (;*str && isspace(*str);str++);
			
			s=str;
			len=0;
	
			if (i==max_args-1)
				break;
		}
	}

	if (len) {
			char *narg;

			narg=malloc(len+1);
			strncpy(narg,s,len);
			narg[len]=0;

			argv[i++]=narg;
	}

	argv[i]=0;

	return i;
}

int main(int argc, char **argv) {
	
	char 	combuf[1024];
	
	char	*prompt = "myshell> ";
	int		sd;
	int 	flags=O_RDONLY;

	// char	*host="localhost";
	char	*host="127.0.0.1";
	int	port=MYSERVER_PORT_ADDRESS;
	struct sockaddr_in sa_in[1];

	char	*prot="tcp";
	
	char	errbuf[256];
	int 	rc=0;

	ProgramName= *argv;
	errbuf[0]=0;

	if ((sd=init_client_connection(host,port,sa_in)) < 0) {
		fprintf(stderr,"Error: %s\n", strerror(errno));
		return -1;
	}

	fprintf(stderr, "\n%s", prompt);

	while (fgets(combuf, sizeof(combuf), stdin) != NULL) {
		ProcessCommand(combuf, sd);
	
		fprintf(stderr, "\n%s", prompt);
	}

	shutdown(sd,2);
	close(sd);
}
