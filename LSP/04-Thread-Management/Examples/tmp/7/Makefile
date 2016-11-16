CFLAGS="-lpthread"
DIR="$(shell pwd)"
j=1

all: run clean

run: ex1
	-@mkdir 1 2
	-for i in 1 2 ; do \
		cd ${DIR}/$$i ; \
		mkdir $${i}1 $${i}2 ; \
		for j in 1 2 ; do \
			cd ${DIR}/$${i}/$${i}$${j} ; \
			touch file_$${i}_$${j}.tst ; \
		done ; \
	done
	./ex1 . file_a_a.tst

ex1: ex1.c

clean:
	rm -fr ex1 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p
