all: run clean
	@make -s clean

run: ex1
	@echo ">>>>  run \"make ex1; ./ex1;\" not from Makefile <<<<"
	@echo ">>>>  strace ./ex1;  and, from another window"
	@echo ">>>>  run kill -9 <PID>"

ex1: ex1.c

clean:
	rm -f ex1 core.*
