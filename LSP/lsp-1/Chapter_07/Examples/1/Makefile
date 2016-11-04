all: run rundbg clean

run:
	# (ps -leaf | grep -v grep | grep ls 1>&2 ) &
	@echo "Hit \"q\" to exit out of the strace window on the next iteration."
	@echo "you'll see the receipt of SIGPIPE."
	sleep 5
	echo "Hello World" 1>/tmp/new.txt | cat
	echo "Hello World" 2>/tmp/new.txt 1>&2 | cat
	#./ex1.sh

rundbg:
	./ex1dbg.sh

clean:

