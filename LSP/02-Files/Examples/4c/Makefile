all: run clean

run: prep
	./ex1
	cp myfile.txt myfile2.txt
	cat myfile.txt > myfile3.txt
	ls -lh myfile*.txt*
	du -kh myfile*.txt*
	gzip myfile.txt
	ls -lh myfile*.txt*
	du -kh myfile*.txt*
	gunzip myfile.txt
	ls -lh myfile*.txt*
	du -kh myfile*.txt*

prep: ex1

ex1: ex1.c

clean:
	rm -f ex1 myfile*.t* my*.txt
