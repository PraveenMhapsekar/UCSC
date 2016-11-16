all: run clean

run: ex1
	-./ex1
	LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH} ldd ./ex1
	ls -l ./ex1
	strip ex1
	LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH} ./ex1
	ls -l ./ex1

ex1:	ex.c ex.h libMYLIBRARY.so
	gcc -c -o ex.o ex.c
	gcc -o ex1 ex.o -L. -lMYLIBRARY
	ldd ./ex1
	ls -l ./ex1

libMYLIBRARY.so: ex2.c ex.h
	gcc -fPIC -c -o ex2.o ex2.c
	gcc -shared -o libMYLIBRARY.so ex2.o
	#nm libMYLIBRARY.so

clean: 
	rm -f ex1 ex2.o libMYLIBRARY.so ex.o
