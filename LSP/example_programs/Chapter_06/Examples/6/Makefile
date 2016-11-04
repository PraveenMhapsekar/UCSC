PARM1 = "Makefile"

all: run clean

run: ex1
	(./ex1; echo $$ )
	nm ./ex1
	ls -l ./ex1
	readelf -a ./ex1 > ex1-readelf.pre-strip
	strip ./ex1
	nm ./ex1
	ls -l ./ex1
	readelf -a ./ex1 > ex1-readelf.post-strip


ex1: ex1.c ex1.h
	(gcc -o ex1 ex1.c; echo $$ )

clean:
	rm -f ex1 ex1.o ex1-readelf.pre-strip ex1-readelf.post-strip

.PHONY: all run clean
