PWD:="`pwd`"
all: run clean

run: ex1
	# chmod 755 ./ex1
	ls -l /usr/bin/passwd /etc/passwd
	chmod 4755 ./ex1
	ls -l ./ex1
	sleep 5;
	id raghav
	-su - raghav -c "cd $(PWD); ./ex1 ex1"

ex1:ex1.c

passwd:
	ls -l `type -p passwd`
	ls -l /etc/passwd /etc/shadow

clean:
	rm -f ex? ex1.sh 
