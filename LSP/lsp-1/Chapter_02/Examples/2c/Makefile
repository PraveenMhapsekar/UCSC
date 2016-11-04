all: run clean

run: ex1 
	touch myfile.txt 
	-./ex1
	ls -l myfile.txt
	cat myfile.txt

clean:
	rm -f ex? myfile.txt 
