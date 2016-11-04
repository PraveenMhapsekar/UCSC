all: run clean

LDFLAGS="-lpthread"

run: ex1 ex2 ex3
	time ./ex1 #
	time ./ex2 #
	time ./ex3 #

ex1: ex1.c

ex2: ex2.c

ex3: ex3.c

clean:
	rm -f ex?
