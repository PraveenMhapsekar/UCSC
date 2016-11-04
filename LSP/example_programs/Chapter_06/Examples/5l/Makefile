PARM1 = "Makefile"

all: run clean

run: ex1
	ls -l 
	(PARM1=${PARM1} ./ex1; ps -f; echo $$ )

ex1: ex1.c ex1.h
	(gcc -g -o ex1 ex1.c; echo $$ )

clean:
	rm -f ex1
