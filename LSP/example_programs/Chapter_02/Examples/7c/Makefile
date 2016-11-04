all: run clean

run: prep
	./ex1
	@make -s clean

prep: ex1
	echo "This is line 1." >myfile.txt
	echo "This is also line 1." >>myfile.txt
	echo "" >>myfile.txt
	echo "This is line 1, yet again." >>myfile.txt

ex1: ex1.c

clean:
	rm -f ex? myfile.txt
