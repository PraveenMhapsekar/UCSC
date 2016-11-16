all: run clean

run: 
# simple/regular file
	echo "This is a test!!" > myfile.txt
	ls -l myfile.txt
# simple/regular directory
	-mkdir mydir
# hardlink to a file
	-ln myfile.txt hardlink.txt
# softlink to a file
	-ln -s myfile.txt softlink.txt
# create a pipe
	-mkfifo myfifo
# create a chardev
	-mknod mychardev c 32 0
# create a blkdev
	-mknod myblkdev b 32 0
	ls -ild mydir myfile.txt hardlink.txt softlink.txt myfifo mychardev myblkdev

clean:
	rm -fr mydir myfile.txt hardlink.txt softlink.txt myfifo mychardev myblkdev
