all: run clean

run: ex1
	./ex1
	getconf -a | grep LONG
	cat /proc/cpuinfo | grep address
	
ex1: ex1.c

clean:
	rm -f ./ex?
