DIR="$(shell pwd)"
LDFLAGS="-lpcre"
LDFLAGS2="-lpthread"

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
	./ex1 . file_a_b.tst
	./ex1 /etc host

ex1: mtf-config.h mtf-direntry.h mtf-dirwalk.h  mtf-match.c mtf-direntry.c  mtf-dirwalk.c mtf-main.c mtf-match.h
	cc -o ex1 mtf-match.c	mtf-direntry.c mtf-dirwalk.c mtf-main.c ${LDFLAGS} ${LDFLAGS2}

clean:
	rm -fr ex1 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p
