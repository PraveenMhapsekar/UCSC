all: run clean

run: ex1
	./ex1 

ex1: ex1.c ex1.h
	gcc -o ex1 ex1.c

clean:
	rm -f ex1
