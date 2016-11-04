all: run clean

run: prep
	touch myfile.dat
	-mkdir mydir.dat
	-mkfifo mypipe.dat
	-ln myfile.dat myhardlink.dat
	-ln -s myfile.dat mysoftlink.dat
	-mkdir /tmp/temp_ch2; cp ./[lMa]* /tmp/temp_ch2
	-./ex1 /tmp/temp_ch2

prep: ex1

ex1: ex1.c

clean:
	rm -fr ex? my*dat /tmp/temp_ch2
