IF:="eth1"
IF:="em1"
IF:="p1p1"

all:  run clean

run: ex1
	ifconfig ${IF}
	./ex1 ${IF} 200.201.202.203
	ifconfig ${IF}

ex1: ex1.c

clean: 
	ifconfig ${IF} down	
	ifconfig ${IF}
	rm -f ex1
