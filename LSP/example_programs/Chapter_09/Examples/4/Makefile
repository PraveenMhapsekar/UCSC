CFLAGS="-g"
LDFLAGS="-lpthread"

all: run wipe

server: ex1s myserver.dat

client: ex1c 

run: ex1c ex1s myserver.dat
	sync
	./ex1s &
	sync;sync;sync;
	sleep 2
	-./ex1c 
	@echo "###############################"
	@echo "# re-run client again."
	@echo "###############################"
	-./ex1c 
	-netstat -an | grep 20011 | grep tcp
	
ex1c: ex1c.c ex1.h

ex1s: ex1s.c ex1.h

gendata: gendata.c

getdata: getdata.c

myserver.dat: gendata getdata
	sync; sync; sync;
	./gendata

clean:
	rm -f ex1? ge?data myserver.dat

wipe: clean telnet
	sync; sync; sync;

telnet:
	-telnet localhost 20011
