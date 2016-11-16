all: run run2 ex1b clean

run: ex1 
	./ex1

run2: ex1a 
	./ex1a

ex1: ex1.c ex1a.c
	gcc -o ex1 ex1.c ex1a.c

ex1a: ex1.c ex1a.c
	gcc -c ex1.c
	gcc -c ex1a.c
	gcc -o ex1a ex1.o ex1a.o

ex1b: ex1.o ex1a.o
	gcc -o ex1b ex1.o ex1a.o

clean:
	rm -f ex1 ex1a ex1b ex1.o ex1a.o

.PHONY: run run2 clean
