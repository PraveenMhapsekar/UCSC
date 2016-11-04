all: run clean

run: ex1 ex1_signed ex1_unsigned 
	./ex1
	./ex1_signed
	./ex1_unsigned
	
ex1: ex1.c

ex1_signed: ex1.c
	gcc -Wall -fsigned-char ex1.c -o ex1_signed

ex1_unsigned: ex1.c
	gcc -Wall -funsigned-char ex1.c -o ex1_unsigned

clean:
	rm -f ./ex? ./ex1_signed ./ex1_unsigned
