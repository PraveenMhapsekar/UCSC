all: run clean

run: ex1
	-./ex1

ex1: ex1.c ex1.h
	echo "This is the first rule"
	cc -g -o ex1 ex1.c

ex1: ex1.c 
	echo "This is the second rule"
	cc -o ex1 ex1.c

clean:
	rm -f ./ex1
