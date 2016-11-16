all: run clean

run: ex1
	./ex1

ex1:	ex1.c ex.h libMYLIB.a libMYLIB2.a
	gcc -c ex1.c
	gcc -c ex1c.c
	@echo "# Notice the library specification is positional"
	@echo "# this does not work: gcc -L. -lMYLIB -lMYLIB2 ex1.o -o ex1"
	@echo "# While the following works!"
	gcc ex1.o ex1c.o -o ex1 -L. -lMYLIB -lMYLIB2
	
libMYLIB.a: ex1a.c ex.h
	gcc -c ex1a.c
	ar cru libMYLIB.a ex1a.o
	
libMYLIB2.a: ex1b.c ex.h
	gcc -c ex1b.c
	ar cru libMYLIB2.a ex1b.o

bad: ex1
	gcc -L. -lMYLIB -lMYLIB2 ex1.o -o ex1
	##  gcc -L. -lMYLIB2 -lMYLIB ex1.o -o ex1

tst:	ex1.c ex.h libMYLIB.a libMYLIB2.a
  ## note that the following works.
	gcc ex1.o -o ex1 -L. -lMYLIB2 -lMYLIB

clean: 
	rm -f ex1 *.o *.a 
