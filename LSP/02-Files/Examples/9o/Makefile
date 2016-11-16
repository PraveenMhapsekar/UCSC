all: run clean

run: ex1
	-strace ./ex1 2>&1 | tail

ex1: ex1.c

clean:
	-@rm -fr ex? 
