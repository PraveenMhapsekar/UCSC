CFLAGS="-lpthread"
DIR="$(shell pwd)"
j=1

all: run clean

run: ex1
	-@mkdir 1 2
	-for i in 1 2 ; do \
		for j in 1 2 ; do \
			cd ${DIR}/$$i ; \
			mkdir $${i}$${j} ; \
			cd ${DIR}/$${i}/$${i}$${j} ; \
			touch file_$${i}_$${j}.tst ; \
		done ; \
	done
	./ex1 . 

ex1: ex1.c

clean:
	rm -fr ex1 1 2 
