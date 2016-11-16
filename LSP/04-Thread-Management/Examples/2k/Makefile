all: run clean

LDFLAGS="-lpthread"

run: ex1
	-./ex1 &
	ps -mL
	sleep 2
	ps -mL

ex1: ex1.c

clean:
	-ls -l ex1 core*
	rm -f ex1 core*
