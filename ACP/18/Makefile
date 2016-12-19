all: run clean

run: prep
#	echo "1st input file"
	cat praveen-assignment-18-input-1.doc
#	echo "2nd input file"
	cat praveen-assignment-18-input-2.doc
	./praveen-assignment-18
	cat praveen-assignment-18-output.doc
prep: praveen-assignment-18 

praveen-assignment-18: praveen-assignment-18.c linkedList.c

clean:
	rm -f praveen-assignment-18
