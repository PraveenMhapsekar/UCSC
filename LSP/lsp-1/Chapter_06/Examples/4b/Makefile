all: run run2 clean

run: ex1-E.c
	cat ex1-E.c | tail

run2: ex2 ex2-E.c
	cat ex2-E.c | tail

ex1-E.c:
	cc -E -o ex1-E.c ex1.c

ex2:
	@echo ">>>>>> NOTE:  MACRO substitution Error HERE <<<<<<"
	-cc -o ex2 ex2.c
	@echo '>>>>>>>>>>>>>>>>>>>>>>  <<<<<<<<<<<<<<<<<<<<<<<<<<"

ex2-E.c:
	cc -E -o ex2-E.c ex2.c

clean:
	rm -f ex1-E.c ex2-E.c ex2
