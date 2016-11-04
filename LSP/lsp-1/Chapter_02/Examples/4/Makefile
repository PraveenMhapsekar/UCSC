all: run clean

run: prep
	echo "Hello World!" >> myfile.txt
	echo "Hello World, 1!" >> myfile.txt
	echo "Hello World, 2!" >> myfile.txt
	echo "Hello World, 3!" >> myfile.txt
	echo "Hello World, 4!" >> myfile.txt
	echo "Hello World, 5!" >> myfile.txt
	./ex1
	ls -l myfile.txt
	cat myfile.txt
	du -kh myfile.txt
	# strace -o strace.3.out ./ex3

prep: ex1 ex3

ex1: ex1.c

clean:
	rm -f ex? myfile.txt strace.*
