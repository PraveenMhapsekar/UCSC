PARM1="World"

PARM2="a"

all: run clean

run: ex1
	PARM1=${PARM1} PARM2=${PARM2} ./ex1
	@PARM2="aa" make -C aa 
	@PARM2="ab" make -C ab 

ex1: ex1.c ex1.h
	gcc -o ex1 ex1.c

clean:
	rm -f ex1
