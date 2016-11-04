CFLAGS="-g"

all: run clean

run: ex1
	-./ex1 i6 0:0:0:0:0:0:0:0
	-./ex1 i6 1:0:0:0:0:0:0:8
	-./ex1 i6 0:0:0:0:0:FFFF:204.152.189.116
	-./ex1 i4 127.0.0.1
	-./ex1 i4 localhost

ex1: ex1.c

clean:
	rm -f ex1 ex1? 
