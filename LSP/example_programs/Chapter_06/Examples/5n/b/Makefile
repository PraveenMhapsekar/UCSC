PARM1="Universe"

PARM2="b"

all: run clean

run: ex1
	PARM1=${PARM1} PARM2=${PARM2} ./ex1

ex1: ex1.c ex1.h
	gcc -o ex1 ex1.c

clean:
	rm -f ex1
