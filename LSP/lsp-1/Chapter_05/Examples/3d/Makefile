all: run clean

run: ex1
	echo "This is line 1." > myfile.txt
	echo "This is also line 1." >> myfile.txt
	echo "This is line 1, again." >> myfile.txt
	echo "" >> myfile.txt
	echo "This is line 1, yet again." >> myfile.txt
	cp ex1.c ex2.c
	-./ex1 ex2.c ex2.bak
	ls
	ls -l

ex1: ex1.c

clean:
	rm -f ex1 mytempfile* ex2* myfile.txt
