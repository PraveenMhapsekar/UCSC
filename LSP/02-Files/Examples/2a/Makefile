all: run clean

run: ex1 
	-ls -l myfile.txt
	strace ./ex1 
	ls -l myfile.txt
	echo "This is a test" > myfile.txt
	ls -l myfile.txt
	./ex1
	ls -l myfile.txt

clean:
	rm -f ex? myfile.txt 
