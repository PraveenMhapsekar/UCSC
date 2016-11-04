all: clean run 

run: ex1
	@echo "Run pmap <PID> and pstack <PID>"
	@echo "run \"time ./ex1\" and type \"Hello World\" and hit enter. then hit ^C.  Notice the output of the time command."   
  

## try this one too, and notice the output of /usr/bin/time
run2: ex1		
	echo "run \"/usr/bin/time ./ex1\""   

ex1: ex1.c

clean:
	rm -f ./ex?
