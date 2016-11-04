
all: run clean

run:  prep
	-./ex1
	ls -l /tmp/ch2 | tail
	df -kh /tmp/ch2
	df -ih /tmp/ch2

prep: ex1
	-mkdir -p /tmp/ch2 			# create a mount point:
	-mke2fs /dev/ram0 				# mount the ramdisk:
	-mount /dev/ram0 /tmp/ch2	# create a filesystem:
	df -k /tmp/ch2
	ls -l /tmp/ch2
	cp /etc/passwd /tmp/ch2
	ls -l /tmp/ch2

ex1: ex1.c

clean: 
	-umount /dev/ram0
	-rm -fr /tmp/ch2 ./ex1
	
