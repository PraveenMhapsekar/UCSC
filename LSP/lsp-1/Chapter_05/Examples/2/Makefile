all: run clean

run: ex1
	-./ex1 &
	sleep 20
	pkill ex1
	@echo "see Portability in man signal()"
	sleep 10
	man signal

ex1: ex1.c

clean:
	rm -f ex?
