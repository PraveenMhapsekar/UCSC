#define MYSERVER_PORT_ADDRESS 24024
#define MYSERVER_DATA_FOUND "LineNumber Found"
#define MAXLINES 5

#define MYSERVER_CLIENTS 2
#define MYSERVER_SOCKET_READ_TIMEOUT 240
#define MYSERVER_DATA_FILE "myserver.dat"

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef SA_RESTART
	#define SA_RESTART 0x000004
#endif

struct Example {
  int linenum;
  char data[50];
};

typedef struct Example Example;
