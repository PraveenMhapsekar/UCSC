all: run clean

run: ex1 
	touch myfile.txt
	./ex1

run2: ex1 
	# cp ./ex1.c myfile.txt
	# chmod 777 myfile.txt
	./ex1
	ls -l
	@make -s clean

clean:
	rm -f ex? myfile.txt ex1-E.c
