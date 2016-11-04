all: run clean

run: ex1
	echo "This is a test." > myfile.txt
	echo "This is a test, again." >> myfile.txt
	echo "This is a test, yet again." >> myfile.txt
	-./ex1

clean:
	rm -f ./ex? myfile.txt
