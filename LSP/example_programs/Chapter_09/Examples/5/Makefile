all: run clean

run: ex1
	for i in `ip -o link|awk '{print $$2}'|sed 's/://g'|sort -u` ; do \
		echo "$$i: `./ex1 $$i 2>&1`"; \
	done

ex1: ex1.c

clean: 
	rm -f ex1
		

