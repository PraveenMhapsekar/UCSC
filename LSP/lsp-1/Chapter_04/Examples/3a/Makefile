all: run clean

LDFLAGS="-lpthread"

run: ex1
	@echo "Note the value of rc when thread attr=DETACHED vs JOINABLE"
	./ex1

ex1: ex1.c

clean:
	rm -f ex1
