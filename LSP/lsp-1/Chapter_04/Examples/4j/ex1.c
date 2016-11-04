#include <stdio.h>
#include <sched.h>

int main() {

	int cpu=0;

	cpu=sched_getcpu();

	fprintf(stderr,"Process/Thread is currently on CPU #%d.\n", cpu);

	return 0;
}
