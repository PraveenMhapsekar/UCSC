PARM1 = "Universe"

all: run clean

run: ex1
	export PARM1="WORLD"; ./ex1; echo
	./ex1; echo
	export PARM1="GALAXY"; ./ex1; echo 
	./ex1; echo

ex1: ex1.c ex1.h
	(gcc -o ex1 ex1.c; echo )

clean:
	rm -f ex1
