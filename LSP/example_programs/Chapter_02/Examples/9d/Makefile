all: run clean

run: ex1
	echo "myfile.dat" > myfile.dat
	-./ex1 < myfile.dat
	##
	mkdir mydir.dat
	echo "mydir.dat" > myfile.dat
	-./ex1 < myfile.dat
	##
	mkfifo mypipe.dat
	echo "mypipe.dat" > myfile.dat
	-./ex1 < myfile.dat
	##
	ln myfile.dat my_hardlink.dat
	echo "my_hardlink.dat" > myfile.dat
	-./ex1 < myfile.dat
	##
	ln -s myfile.dat my_softlink.dat
	echo "my_softlink.dat" > myfile.dat
	-./ex1 < myfile.dat

clean:
	rm -fr ex? my*.dat
