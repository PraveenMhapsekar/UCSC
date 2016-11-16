CFLAGS="-lpthread"
DIR="$(shell pwd)"
j=1

all: run clean
	@make clean >/dev/null 2>/dev/null

run: prep ex1 
	./ex1 .

run3: prep3 ex1 
	./ex1 .
	@make clean >/dev/null 2>/dev/null

prep: 
	-@mkdir 1 2
	-for i in 1 2 ; do \
		for j in a b ; do \
			cd ${DIR}/$$i ; \
			mkdir $${i}$${j} ; \
			cd ${DIR}/$${i}/$${i}$${j} ; \
			touch file_$${i}_$${j}.tst ; \
		done ; \
	done

prep3: 
	-@mkdir 1 2
	-for i in 1 2 ; do \
		for j in A B ; do \
			cd ${DIR}/$$i ; \
			mkdir $${i}$${j} ; \
			cd ${DIR}/$${i}/$${i}$${j} ; \
			for k in a b ; do \
				cd ${DIR}/$${i}/$${i}$${j} ; \
				mkdir $${i}$${j}$${k} ; \
				cd ${DIR}/$${i}/$${i}$${j}/$${i}$${j}$${k}/ ; \
				touch file_$${i}_$${j}_$${k}.tst ; \
			done ; \
		done ; \
	done

ex1: ex1.c

clean:
	rm -fr ex1 1 2 
