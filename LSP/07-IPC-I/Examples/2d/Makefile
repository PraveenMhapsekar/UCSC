all: run clean

run: ex1
	-@time strace ./ex1

ex1: ex1.c

clean:
	rm -f ex1 core.*
