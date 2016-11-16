#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

// see man CPU_SET

int main() {

	int cpu=0;
	cpu_set_t mask[1];

	// cpu=sched_getaffinity(getpid(),size,cpu_set_t);
	cpu=sched_getaffinity(0,sizeof(cpu_set_t), mask);

	// see man CPU_SET
	fprintf(stderr,"Process/Thread affinity is CPU #%x.\n",  *mask);

	return 0;
}
