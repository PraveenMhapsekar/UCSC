all: run clean

run: compile
	./ex1a_init
	./ex1b_demo
	./ex1c_rm

compile: ex1a_init ex1b_demo ex1c_rm

ex1a_init: ex1a_init.c 

ex1b_demo: ex1b_demo.c 

ex1c_rm: ex1c_rm.c

clean:
	rm -f ex1[ab]_???? ex1c_??
