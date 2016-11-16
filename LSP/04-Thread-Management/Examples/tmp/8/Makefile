CFLAGS="-lpthread"
DIR="$(shell pwd)"
j=1

all: run clean

run: ex1
	-@mkdir 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p
	-for i in 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p; do \
		cd ${DIR}/$$i ; \
		mkdir 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p ; \
		for j in 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p; do \
			cd ${DIR}/$$i/$$j ; \
			touch file_$${i}_$${j}.tst ; \
		done ; \
	done
#	./ex1

ex1: ex1.c

clean:
	rm -fr ex1 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p
