all: run clean

run: ex1
	time ./ex1   #/usr/bin/time ./ex1

## try this one too, and notice the output of /usr/bin/time
run2: ex1		
	/usr/bin/time ./ex1   

## try this one again, and, notice the output of the 'time' command
run3: ex1		
	time ./ex1   

ex1: ex1.c

clean:
	rm -f ./ex?
