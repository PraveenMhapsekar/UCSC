CFLAGS="-g"
LDFLAGS="-lpthread"

all: run wipe

server: ex1s 

client: ex1c 

run: ex1c ex1s
	sync
	-./ex1s 127.0.0.1 27027 &
	sync
	sleep 2
	-netstat -a | grep 27027 | grep udp
	-./ex1c 127.0.0.1 27027 "Hello World!"
	
ex1c: ex1c.c 

ex1s: ex1s.c

clean:
	rm -f ex1? 

wipe: clean telnet
	sync; sync; sync;

telnet:
	-telnet localhost 27027
