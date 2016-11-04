all: run clean

run: named_pipe.sh
	(./named_pipe.sh; sleep 30)

clean: 
	rm -f /tmp/mkfifo
