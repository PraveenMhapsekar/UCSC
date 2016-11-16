all: run clean

run: ex1
	-./ex1

ex1: ex1.c


ex1_use_SELECT: ex1.c
	gcc -Duse_SELECT -o ex1_use_SELECT ex1.c

clean:
	rm -f ex1 ex1_* core*
