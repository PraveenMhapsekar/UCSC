all: clean run 

run: ex1
	ls -l ex1 ex1-E.c
	file ex1 ex1-E.c
	

ex1: ex1.c
	cc -E ex1.c > ex1-E.c
	cc -o ex1 ex1.c

clean: 
	rm -f ex1 ex1-E.c
	



