all: run clean

run: prep
	-./ls1 ls1*	
	touch aa.dat
	chmod 000 aa.dat
	ls -l aa.dat
	-./ls1 aa.dat

prep: ls1 

ls1: ls1.c

clean:
	rm -f ls? aa.dat




