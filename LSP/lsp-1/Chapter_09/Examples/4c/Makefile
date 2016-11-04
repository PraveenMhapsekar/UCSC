CFLAGS="-g"

all: run wipe

server: ex1s myserver.dat

client: ex1c 

run: mylib ex1c ex1s myserver.dat
	-LD_LIBRARY_PATH=.:$${LD_LIBRARY_PATH} ./ex1s &
	-LD_LIBRARY_PATH=.:$${LD_LIBRARY_PATH} ldd ./ex1s
	sleep 2
	-LD_LIBRARY_PATH=.:$${LD_LIBRARY_PATH} ./ex1c
	@echo "###########################"
	@echo "re-run client, again.      "
	@echo "###########################"
	-LD_LIBRARY_PATH=.:$${LD_LIBRARY_PATH} ./ex1c
	-netstat -an | grep 22011 | grep tcp
	
ex1c: mylib ex1c.c ex1.h
	cc ${CFLAGS} -o ex1c ex1c.c -L. -lmylib

ex1s: ex1s.c ex1.h
	cc ${CFLAGS} -o ex1s ex1s.c -L. -lmylib

gendata: gendata.c

getdata: getdata.c

myserver.dat: gendata getdata
	sync
	./gendata

clean:
	rm -f ex1? ge?data myserver.dat libmylib.a *.o *.so

wipe: clean telnet

telnet:
	telnet localhost 21011

init_client_connection: init_client_connection.c
	gcc -fPIC -o init_client_connection.o -c init_client_connection.c

init_server_connection: init_server_connection.c
	gcc -fPIC -o init_server_connection.o -c init_server_connection.c

mylib: init_client_connection init_server_connection
	gcc -shared -o libmylib.so init_client_connection.o init_server_connection.o
	rm -f *.o
