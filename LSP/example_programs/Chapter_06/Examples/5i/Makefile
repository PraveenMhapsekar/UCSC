CFLAGS="-E"

all: run run2 clean

run: ex1.mod.c

run2: ex1
	file ex1*
	ls -l

ex1.mod.c: 
	cc $(CFLAGS) -o ex1.mod.c ex1.c
	## cc -o ex1.mod.c ex1.c

clean:
	rm -f *mod* ex1
