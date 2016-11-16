#include <stdio.h>
#include <sched.h>

int main() {

	int cpu=0;

/*
       Glibc  does  not  provide a wrapper for getcpu() system call; 
		   call it using syscall(2); or use sched_getcpu(3) instead.
*/

  int c, s;
	// s = getcpu(&c, NULL, NULL);
	// 318 from  /usr/include/asm/unistd_32.h  ... /usr/include/unistd.h 

  // fork  ... s=syscall(2,NULL,NULL,NULL);
  // open  ... s=syscall(5,"./myfile.txt",O_WRONLY|O_TRUNC|O_CREAT,NULL);

	s=syscall(318,&c,NULL,NULL);
	cpu = (s == -1) ? s : c;

	fprintf(stderr,"Process/Thread is currently on CPU #%d.\n", cpu);

	// fork
	s=syscall(2,NULL,NULL,NULL);
	fprintf(stderr,"Process/Thread %d is currently on CPU #%d.\n", getpid(), cpu);
	
	return 0;
}
