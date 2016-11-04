all: clean run 

run: ex1
	@echo "run \"time ./ex1\" then hit ^C after a few seconds.  Notice the output of the time command."   

## try this one too, and notice the output of /usr/bin/time
run2: ex1		
	echo "run \"/usr/bin/time ./ex1\""   

ex1: ex1.c

clean:
	rm -f ./ex?
