#define _POSIX_SOURCE 1

#define BUFSZ 512
#define ERRBUFSZ 512

#define MYSH_PROMPT "mysh> "

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>

void do_cmd(char *buf, int len, int linenum, char *errbuf);
int parse_cmd(char *buf, char **vbuf, char *errbuf);
int builtin_cmd(char **argv, int linenum);
int process_cmd(char **argv, int linenum);
int printwaitstatus(FILE *wfp, int pid, int st);

int printwaitstatus(FILE *wfp, int pid, int st) {

	fprintf(wfp,"\n");

	fprintf(wfp,"%6d=wait()",pid);

	if (WIFEXITED(st)) {
		fprintf(wfp,"exit: %3d\n", WEXITSTATUS(st));
	}
	else if (WIFSTOPPED(st)) {
		fprintf(wfp,"stop status: %3d\n", WSTOPSIG(st));
	}
	else if (WIFSIGNALED(st)) {
		fprintf(wfp,"termination signal: %3d\n", WTERMSIG(st));
		
		// fprintf(wfp,"\tcore dump: %s\n", WIFCORE(st) ? "yes" : "no");
	}

	return 0;
}
	

int builtin_cmd(char **argv, int linenum) {

	int st;

	if ((strcmp(*argv,"exit") == 0) ||
		  (strcmp(*argv,"ex") == 0) || 
		  (strcmp(*argv,"quit") == 0) || 
		  (strcmp(*argv,"q") == 0) ) {
		exit(0);
	}
	else if (strcmp(*argv,"cd") ==0) {
		if ((argv[1]) && (st=chdir(argv[1])) != 0) {
			fprintf(stderr,"ERR: \"cd\" to '%s' failed! (Line=%d)\n",
				argv[1],linenum);
			return -1;
		}
		return 1;
	}
	else if (strcmp(*argv,"hello") ==0) {
			fprintf(stderr,"\nHello! from process '%d'. (Line=%d)\n",
				getpid(),linenum);
		return 1;
	}

	return 0;
}
	
int process_cmd(char **argv, int linenum) {

	pid_t	cpid=fork();
	
	if (cpid<0) {
		fprintf(stderr,"ERR: \"fork\" error! (Line=%d)\n",
			linenum);
		exit (-1);
	}
	else if (cpid==0) {
		if (execvp(argv[0],argv) < 0) {
			fprintf(stderr,"ERR: \"execv(%s)\" error! (Line=%d)\n",
			argv[0], linenum);
			_exit (errno);
		}
	}
	else {
		int st;
	
		cpid=wait(&st);
		// printwaitstatus(stdout,cpid,st);
	}
}
		
int parse_cmd(char *buf, char **vbuf, char *errbuf) {

	int i=0;

	char *delim=" ,\t\n";

	char *tok;

	tok=strtok(buf,delim);

	while (tok) {
		vbuf[i]=(char *)malloc(BUFSZ*sizeof(char));
		
		strcpy(vbuf[i],tok);

		tok=strtok(NULL,delim);
		i++;
	}
	
	vbuf[i]=0;

	return i;
		
}
	

void do_cmd(char *buf, int len, int linenum, char *errbuf) {

	int i=0;
	char *vbuf[128];	
		
	int maxargs=sizeof(vbuf)/sizeof(char *);
	int numargs;

	if ((numargs=parse_cmd(buf,vbuf,errbuf))==maxargs) {
		fprintf(stderr,"ERR: too many args (Line=%d)\n",linenum);
	}
	else {
		if (!builtin_cmd(vbuf,linenum) ) {
			process_cmd(vbuf,linenum);
		}
	}

	for (i=0;i<numargs; i++) {
		free(vbuf[i]);
	}

	return;
}

int main(int argc, char **argv) {
	
	int i;

	int st;

	int linenum=0;
	
	char *buf=(char *)malloc(BUFSZ*sizeof(char)); 
	char *errbuf=(char *)malloc(ERRBUFSZ*sizeof(char)); 

	char *mysh = MYSH_PROMPT;

	FILE *rfp=stdin;

	if (isatty(fileno(rfp))) {
		mysh="mysh> ";
	
		fprintf(stderr,"%s",mysh);
	}

	while (fgets(buf,BUFSZ,rfp)) {
		linenum++;

		buf[strlen(buf)-1]=0;

		if (*buf)
			do_cmd(buf, BUFSZ, linenum,errbuf);
	
		if (mysh) 
			fprintf(stderr,"%s",mysh);
	}
}
