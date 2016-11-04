# DEV := "/dev/cdrom"
DEV := "/dev/sr0"

all: run clean

run: ex1 cdrom_disc_status
	ls -l ${DEV}
	-./cdrom_disc_status ${DEV}
	-umount ${DEV} 2>/dev/null
	-./ex1 ${DEV}

clean:
	rm -f ex1 cdrom_disc_status
