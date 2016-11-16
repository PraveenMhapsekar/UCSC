LDFLAGS:="-lpthread"

all: run clean

run: ex1
	cp ex1.c ex2.c
	-./ex1 ex2.c ex2.bak
	ls -l

ex1: ex1.c

clean:
	rm -f ex1 ex2* my*
