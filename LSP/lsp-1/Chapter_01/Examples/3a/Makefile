all: run clean

run:ex1
	@echo "Run pmap <PID> and pstack <PID>"
	time ./ex1 #
	strace -o ex1.strace ./ex1

ex1: ex1.c

clean: 
	rm -f ex? ex??
