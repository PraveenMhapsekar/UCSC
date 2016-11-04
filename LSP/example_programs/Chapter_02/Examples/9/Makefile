
all: run clean

run:  prep eg1 eg2 eg3

eg1: ex1
	-./ex1
	ls -l /tmp/ch2 | tail
	df -kh /tmp/ch2
	df -ih /tmp/ch2
	read x # sleep 5
	-rm -f /tmp/ch2/ch2_*

eg2: largefile
	./largefile
	ls -l /tmp/ch2 | tail
	df -kh /tmp/ch2
	df -ih /tmp/ch2
	read x # sleep 5
	-rm -f /tmp/ch2/ch2_*

eg3: largefile2
	./largefile2
	ls -l /tmp/ch2 | tail
	df -kh /tmp/ch2
	df -ih /tmp/ch2
	read x # sleep 5
	-rm -f /tmp/ch2/ch2_*

prep: ex1 largefile largefile2
	-mkdir -p /tmp/ch2 			# create a mount point:
	# -mke2fs /dev/ram0 				# mount the ramdisk:
	mkfs.ext3 /dev/ram0
	-mount /dev/ram0 /tmp/ch2	# create a filesystem:
	df -k /tmp/ch2
	#ls -l /tmp/ch2
	cp /etc/hosts /tmp/ch2
	#ls -l /tmp/ch2

ex1: ex1.c

largefile: largefile.c

largefile2: largefile2.c

clean: 
	-umount /dev/ram0
	-rm -fr /tmp/ch2 ./ex1 ./largefile ./largefile2
