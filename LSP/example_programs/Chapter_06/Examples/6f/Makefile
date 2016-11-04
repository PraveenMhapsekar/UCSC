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
	

libMYLIB.a: myprintf.c ex.h
	gcc -c myprintf.c
	ls -l ./myprintf.o
	ar cru libMYLIB.a myprintf.o
	ar tv libMYLIB.a

clean: 
	rm -f ex1 *.o *.a 
