#!/bin/bash -a

cat>ex4a_stack_initialized.c <<EOS1

/* #4. Stack Initialized Array */
#include <stdio.h>

int main(void) {
	int myarray[50000]={
EOS1

i=1
I=10000
ln=1
LN=12
while [ "$i" -lt "$I" ]
do
	if [ "$ln" -gt "$LN" ]
	then 
		echo "" >> ex4a_stack_initialized.c
	  ln=0
	fi
	echo -n "$i," >> ex4a_stack_initialized.c
	(( i=i+1 )) 
	(( ln=ln+1 )) 
done

cat>>ex4a_stack_initialized.c <<EOS2
	200000};
	int c;

	myarray[0]=1;
	fprintf(stderr,"PID==%d\n",getpid());
	c=getchar(); // to insert a pause for pmap analysis
	return 0;
}
EOS2
