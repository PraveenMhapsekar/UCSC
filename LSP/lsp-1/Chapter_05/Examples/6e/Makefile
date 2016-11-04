LDFLAGS:="-lpthread"

all: run clean

run: ex1
	-./ex1
	ls -l

ex1: ex1.c
	# cc -D use_KILL -o ex1 ex1.c
	cc -o ex1 ex1.c

clean:
	rm -f ex1 
