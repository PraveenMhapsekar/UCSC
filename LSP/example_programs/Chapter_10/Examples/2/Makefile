all: run clean

run: udp_client udp_server 
	./udp_server &
	(sleep 2; ./udp_client;)
	(sleep 1; ./udp_client;)
	(sleep 1; ./udp_client;)

clean:
	rm -f udp_client udp_server
