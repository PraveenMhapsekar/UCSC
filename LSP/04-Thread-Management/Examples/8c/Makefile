CFLAGS="-g"
LDFLAGS="-lpthread"
DIR="$(shell pwd)"
j=1

all: run clean
	-@make clean >/dev/null 2>&1

run: prep ex1 
	-./ex1 . "*ex*"
	@echo "Note: run 'make run3' repeatedly, and note varying results for the \"*host*\" search. Try to fix it."
	#ls -R

run2: prep3 ex1 
	-./ex1 . file_1_A_a.tst
	-@make clean >/dev/null 2>&1

run3: prep3 ex1 
	./ex1 /etc "*hosts*"
	-@make clean >/dev/null 2>&1

prep: 
	-@mkdir 1 2 
	-for i in 1 2 ; do \
		for j in a b ; do \
			cd ${DIR}/$$i ; \
			mkdir $${i}$${j} ; \
			cd ${DIR}/$${i}/$${i}$${j} ; \
			touch file_$${i}_$${j}.tst ; \
			touch textfile_$${i}_$${j}.tst ; \
			# sleep 1 ; \
		done ; \
	done

prep3: 
	-@mkdir 1 2 3
	-@for i in 1 2 3; do \
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
	rm -fr ex? 1 2 ?
