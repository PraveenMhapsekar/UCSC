all: run clean

run: prep
	@echo "This is line 1." >>myfile.txt
	@echo "This is also line 1." >>myfile.txt
	@echo "" >>myfile.txt
	@echo "This is line 1, yet again." >>myfile.txt
	./ex1

prep: ex1

ex1: ex1.c

clean:
	rm -f ex1 myfile.txt
