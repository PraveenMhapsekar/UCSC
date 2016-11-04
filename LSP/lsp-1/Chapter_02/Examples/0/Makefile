all: dbg clean

run:
	cat myfile.txt
	cat < myfile.txt

dbg:
	strace -o strace1.out cat myfile.txt
	strace -o strace2.out cat < myfile.txt
	@echo "#######################################"
	tail -15 strace1.out
	@echo "#######################################"
	sleep 3
	tail -15 strace2.out
	@echo "#######################################"

clean:
	rm -f strace*.out
