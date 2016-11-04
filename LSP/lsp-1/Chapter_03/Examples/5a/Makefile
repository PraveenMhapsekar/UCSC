PWD:="`pwd`"
all: run clean

run: ex1
	@echo "#####################################"
	chmod 4755 ./ex1
	ls -l ./ex1
	-su - raghav -c "cd $(PWD); ./ex1 ex1"
	@echo "#####################################"
	chmod 6755 ./ex1
	ls -l ./ex1
	-su - raghav -c "cd $(PWD); ./ex1 ex1"
	@echo "#####################################"

ex1:ex1.c

clean:
	rm -f ex? ex1.sh 
