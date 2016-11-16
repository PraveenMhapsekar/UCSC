PARM1 = "Makefile"

all: run 

run: ex1
	@echo "now running ex1"

ex1: ex1.c ex1.h
	@make -C a 
	@make -C b  

clean:
	rm -f ex1
