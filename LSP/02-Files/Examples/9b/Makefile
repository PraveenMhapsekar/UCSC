#!/usr/bin/make -if

all: s1 s2 s3

s1: 
	top -n 1 -d 1 | head -5 | tail -2
	free
	echo "To free pagecache-"
	echo 1 > /proc/sys/vm/drop_caches
	top -n 1 -d 1 | head -6 | tail -3 | head -2
	free -t

s2:
	top -n 1 -d 1 | head -5 | tail -2
	free
	echo "To free dentries and inodes-"
	echo 2 > /proc/sys/vm/drop_caches
	top -n 1 -d 1 | head -6 | tail -3 | head -2
	free -t

s3:
	top -n 1 -d 1 | head -5 | tail -2
	free
	echo "To free pagecache, dentries and inodes-"
	echo 3 > /proc/sys/vm/drop_caches
	top -n 1 -d 1 | head -6 | tail -3 | head -2
	free -t

