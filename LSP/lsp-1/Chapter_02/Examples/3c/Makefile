all: run clean

prep:
	echo "=> This is \"myfile.txt\"" > myfile.txt

run: prep
	cat myfile.txt    ## myfile.txt is assigned fd==3.
	cat < myfile.txt  ## myfile.txt is read using fd==0.
	strace -f -o cat1.trc cat myfile.txt
	strace -f -o cat2.trc cat < myfile.txt
	@echo "############################"
	tail cat1.trc
	@echo "############################"
	tail cat2.trc
	@echo "############################"

clean:
	rm -f myfile.txt
