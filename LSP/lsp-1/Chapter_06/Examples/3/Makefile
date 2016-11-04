
all: run clean

run:  prep 
	-./ex.sh

prep: 
	-mkdir -p /tmp/ch6_1b 			# create a mount point:
	# -mke2fs /dev/ram0 				# mount the ramdisk:
	# -mount /dev/ram0 /tmp/ch6_1b	# create a filesystem:

clean: 
	# -umount /dev/ram0
	-ls -1 /tmp/ch6_1b | xargs rm -f
	-rm -fr /tmp/ch6_1b test.tar
  
