all: run clean

run: prep
	@echo "This is line 1." >>myfile.txt
	@echo "This is also line 1." >>myfile.txt
	@echo "" >>myfile.txt
	@echo "This is line 1, yet again." >>myfile.txt
	./ex3

prep: ex3

ex3: ex3.c

clean:
	rm -f ex? myfile.txt
