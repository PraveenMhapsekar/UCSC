all: run clean

run: ex1
	./ex1

ex1:	ex1.c ex.h libMYLIB.a
	gcc -c ex1.c
	@echo "# Notice the library specification is positional"
	@echo "# this does not work: " gcc -L. -lMYLIB ex1.o -o ex1
	@echo "# While the following works!"
	gcc ex1.o -o ex1 -L. -lMYLIB
	# gcc ex1.o -o ex1 -L. 
	ls -l ex1*.o libMYLIB.a ex1
	

libMYLIB.a: ex1a.c ex.h
	gcc -c ex1a.c
	ls -l ./ex1a.o
	ar cru libMYLIB.a ex1a.o
	ls -l libMYLIB.a
	ar tv libMYLIB.a

clean: 
	rm -f ex1 *.o *.a 
