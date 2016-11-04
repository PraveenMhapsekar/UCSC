all: run clean

run: ex1 
	echo "=> This is line 1." >  myfile.txt 
	echo "=> This is also line 1." >>  myfile.txt 
	echo "=> This is line 1, again." >>  myfile.txt 
	echo "=> This is line 1, yet again." >>  myfile.txt 
	./ex1 < myfile.txt
	ls -l myfile.txt myfile.out
	cat myfile.txt
	cat myfile.out

clean:
	rm -f ex? myfile.txt myfile.out
