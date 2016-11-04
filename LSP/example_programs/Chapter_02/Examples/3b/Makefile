all: run clean

run: 
# simple/regular file
	echo "This is a test!!" > myfile.txt
	ls -l myfile.txt
# simple/regular directory
	-mkdir mydir
# hardlink to a file
	-ln myfile.txt myhardlink.txt
# softlink to a file
	-ln -s myfile.txt softlink.txt
# softlink to a softlink
	-ln -s softlink.txt anothersoftlink.txt 
	-ln -s anothersoftlink.txt yetanothersoftlink.txt
# create a pipe
	-mkfifo myfifo
# create a chardev
	-mknod mychardev c 32 0
# create a blkdev
	-mknod myblkdev b 32 0
	ls -iald mydir myfile.txt myhardlink.txt *softlink.txt myfifo mychardev myblkdev . ..  | sort
	@echo "Note: Hard link cannot be created for directories"

clean:
	rm -fr mydir* myfile*.txt* myhardlink.txt softlink.txt myfifo mychardev myblkdev *anothersoftlink.txt yet*txt


