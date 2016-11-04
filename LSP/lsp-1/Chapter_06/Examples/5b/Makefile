ex1: ex1.c ex1.h

run: ex1
	./ex1
	sleep 10; touch ./ex1.h
	ls -l ./ex1.? ./ex1
	#rm -f ex1

recompile: ex1
	ls -l ./ex1.? ./ex1
	@make ex1


clean:
	rm -f ./ex1
