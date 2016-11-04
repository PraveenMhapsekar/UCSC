all: run clean

run: ex1
	touch Wednesday
	ls -l Wednesday
	-./ex1
	rm -f Wednesday
	-./ex1

ex1: ex1.c

clean:
	rm -f ex1 Wednesday
