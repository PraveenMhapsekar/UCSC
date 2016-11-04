all: run clean

run: prep
	./ex1
	cat myfile.txt
	ls -l myfile.txt
	du -kh myfile.txt

prep: ex1

ex1: ex1.c

clean:
	rm -f ex1 myfile.txt
