all: run clean

run:ex1
	time ./ex1 #
	strace -o ex1.strace ./ex1

ex1: ex1.c

clean: 
	rm -f ex? ex??
