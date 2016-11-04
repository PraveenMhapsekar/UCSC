all: run clean

run:  
	-mkdir /tmp/ramdisk 			# create a mount point:
	-mke2fs /dev/ram0 >/dev/null 2>&1 # mount the ramdisk: 
	-mount /dev/ram0 /tmp/ramdisk	# create a filesystem:
	df -k /tmp/ramdisk
	ls -l /tmp/ramdisk
	cp /etc/passwd /tmp/ramdisk
	ls -l /tmp/ramdisk
#
	ln -s /tmp/ramdisk/passwd mypasswd1
	-ln /tmp/ramdisk/passwd mypasswd2
	ls -l

clean: 
	-umount /dev/ram0
	-rm -fr /tmp/ramdisk mypasswd*
