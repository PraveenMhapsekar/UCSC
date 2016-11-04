CFLAGS="-lpthread"
LDFLAGS="-lpcre"
DIR="$(shell pwd)"
j=1

all: run clean

run: prep ex1 
	@echo "this example needs pcre."
	@echo " .. you'll need to do a \"yum install pcre-devel\""
	-./ex1 . file_2_b.tst
	-./ex1 /etc host

run3: prep3 ex1 
	-./ex1 . file_2_A_a.tst
	-./ex1 /etc host*
	-@make clean >/dev/null 2>&1

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
	-@for i in 1 2 ; do \
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
