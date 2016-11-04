#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include <stdio.h>

int main() {

	int cpu=0;

/*
       Glibc  does  not  provide a wrapper for getcpu() system call; 
		   call it using syscall(2); or use sched_getcpu(3) instead.
*/

  int c=0, s=0;
	// s = getcpu(&c, NULL, NULL);

	s=(signed int) syscall(SYS_getcpu,&c,NULL,NULL);
	cpu = (s == -1) ? s : c; // return -1 if err.

	// s=(signed int) syscall(SYS_open,&c,NULL,NULL);

	fprintf(stderr,"Process/Thread is currently on CPU #%d.\n", cpu);

	return 0;
}
