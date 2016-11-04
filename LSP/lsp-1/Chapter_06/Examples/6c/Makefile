all: run clean

run: ex1
	./ex1

ex1:	ex1.c ex.h libMYLIB.a libMYLIB2.a
	gcc -c ex1.c
	@echo "# Notice the library specification is positional"
	@echo "# this does not work: gcc -L. -lMYLIB -lMYLIB2 ex1.o -o ex1"
	@echo "# While the following works!"
	@echo "Also, \"gcc ex1.o -o ex1 -L. -lMYLIB -lMYLIB2\" does not work!"
	gcc ex1.o -o ex1 -L. -lMYLIB2 -lMYLIB
	@echo " try gcc ex1.o -o ex1 -L. -lMYLIB -lMYLIB2 -lMYLIB -lMYLIB2 -lMYLIB"
	
libMYLIB.a: myprintf.c ex.h
	gcc -c myprintf.c
	ar cru libMYLIB.a myprintf.o
	
libMYLIB2.a: myprintf2.c ex.h
	gcc -c myprintf2.c
	ar cru libMYLIB2.a myprintf2.o

bad: ex1
	gcc -L. -lMYLIB -lMYLIB2 ex1.o -o ex1
	##  gcc -L. -lMYLIB2 -lMYLIB ex1.o -o ex1

tst:	ex1.c ex.h libMYLIB.a libMYLIB2.a
  ## note that the following works.
	gcc -c ex1.c
	gcc ex1.o -o ex1 -L. -lMYLIB -lMYLIB2

tst2:	ex1.c ex.h libMYLIB.a libMYLIB2.a
  ## note that the following works.
	gcc -c ex1.c
	gcc ex1.o -o ex1 -L. -lMYLIB -lMYLIB2 -lMYLIB

clean: 
	rm -f ex1 *.o *.a 
