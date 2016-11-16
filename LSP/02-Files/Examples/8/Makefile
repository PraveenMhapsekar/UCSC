all: run clean

run: ex1
	echo "This is a test!!" > myfile.txt
	echo "This is again a test!!" >> myfile.txt
	-./ex1 < myfile.txt

clean:
	rm -f ex? ex?? myfile.txt
