all: run clean

run: ex1 
	touch myfile.txt
	strace ./ex1 2>&1 | tail -12

clean:
	rm -f ex? myfile.txt ex1-E.c
