all: run clean

run: prep
	echo "This is line 1." >>myfile.txt
	echo "This is also line 1." >>myfile.txt
	echo "" >>myfile.txt
	echo "This is line 1, yet again." >>myfile.txt
	./ex2

prep: ex2

ex2: ex2.c

clean:
	rm -f ex? myfile.txt
