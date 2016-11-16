all: run clean

run: ex1 
	touch myfile.txt myfile2.txt myfile5.txt myfile6.txt
	echo "Testing" > myfile5.txt
	./ex1 myfile.txt myfile2.txt myfile3.txt myfile4.txt myfile5.txt myfile6.txt myfile7.txt
	ls -l myfile.txt myfile?.txt

clean:
	rm -f ex? myfile.txt myfile?.txt
