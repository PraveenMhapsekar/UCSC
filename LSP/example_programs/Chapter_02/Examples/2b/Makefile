all: run clean

run: ex1 
	touch myfile.txt 
	strace ./ex1 
	ls -l myfile.txt

clean:
	rm -f ex? myfile.txt core*
