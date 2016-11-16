all: run clean

run: ex1 
	echo "Hello World!" >  myfile.txt 
	-ls -l myfile.txt
	./ex1
	-ls -l myfile.txt
	# rm -f ./myfile.txt
	# strace ./ex1

clean:
	rm -f ex? myfile.txt 
