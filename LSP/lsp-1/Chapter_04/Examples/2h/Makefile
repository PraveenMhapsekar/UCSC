all: run clean

LDFLAGS="-lpthread"

run: ex1 ex2
	time ./ex1 #
	time ./ex2 #

ex1: ex1.c

ex2: ex2.c

clean:
	rm -f ex?
