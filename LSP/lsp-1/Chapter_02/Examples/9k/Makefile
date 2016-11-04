all: run clean

run: prep
	touch myfile.dat
	-mkdir mydir.dat
	-mkfifo mypipe.dat
	-ln myfile.dat myhardlink.dat
	-ln -s myfile.dat mysoftlink.dat
	#-mknod myBLKDEV.dat b 32 0
	#-mknod myCHARDEV.dat c 32 0
	-./ex1 			# No argument needed

prep: ex1

ex1: ex1.c

clean:
	rm -fr ex1 my*dat
