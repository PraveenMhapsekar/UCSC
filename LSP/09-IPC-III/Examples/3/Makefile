CFLAGS="-g"

all: run clean

run: ex1
	./ex1 127.0.0.1 # format #1
	./ex1 localhost	# format #2
	# ./ex1 7F000001 # format #3 127.0.0.1 == 0111111100000000000000000001
	# ./ex1 localhost	# format #3 127.0.0.1 == 0111111100000000000000000001
	./ex1 yahoo.com
	./ex1 www.yahoo.com
	./ex1 google.com
	./ex1 www.google.com

ex1: ex1.c

clean:
	rm -f ex1 ex1? 
