// sourced from http://linux.die.net/man/3/pthread_join

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *ar;
    long n;
} subarray;

void *
incer(void *arg)
{
    long i,j;
		subarray *sb=(subarray *)arg;

    for (i=0; i < sb->n; i++)
        (sb->ar[i])++;

		printf("i=%d\n",i);
	
}

int main(void)
{
		int				 n=2*500000;
    int        ar[n*2];
		int				 i=0;

    pthread_t  th1, th2;
    subarray   sb1, sb2;

		// populate the first 500k members of array
    sb1.ar = &ar[0];	// set start address to first element
    sb1.n  = n;

		incer(&sb1);

    return 0;
}
