#!/usr/bin/make -f

all:	tar_archive	 clean

tar_archive:
	tar cvf all.tar *
	ls -l
	ps -f

clean:
	rm -f all.tar
