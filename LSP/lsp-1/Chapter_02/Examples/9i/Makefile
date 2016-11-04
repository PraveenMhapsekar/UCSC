all: run clean

run: prep
	-./ls5 			# No argument needed

prep: ls5
	touch myfile.dat
	-mkdir mydir.dat
	-mkfifo mypipe.dat
	-ln myfile.dat myhardlink.dat
	-ln -s myfile.dat mysoftlink.dat

ls5: ls5.c

clean:
	rm -fr ls? my*dat




