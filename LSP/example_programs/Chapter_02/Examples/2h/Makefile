all: run clean

run: ex1 
	-./ex1
	-ls -l myfile.txt
	touch myfile.txt
	-./ex1
	-ls -l myfile.txt

clean:
	rm -f ex? myfile.txt 
