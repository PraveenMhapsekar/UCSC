CFLAGS := "-lpthread"

all: run clean

run: ex2
	-strace -o strace.ex1.out -f ./ex2  
	-[ -f "./strace.ex1.out" ] && { tail -15 ./strace.ex1.out; }

ex2: ex2.c

clean:
	rm -f ex2 ./strace.ex1.out
