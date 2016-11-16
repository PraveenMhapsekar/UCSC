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
		int				 n=500000;
    int        ar[n*2];
    pthread_t  th1, th2;
    subarray   sb1, sb2;

		// populate the first 500k members of array
    sb1.ar = &ar[0];	// set start address to first element
    sb1.n  = n;
    (void) pthread_create(&th1, NULL, incer, &sb1);


		// populate subsequent 500k members of array
    sb2.ar = &ar[n];	// set start address to 500k'th element
    sb2.n  = n;
    (void) pthread_create(&th2, NULL, incer, &sb2);

    (void) pthread_join(th1, NULL);
    (void) pthread_join(th2, NULL);

    return 0;
}
