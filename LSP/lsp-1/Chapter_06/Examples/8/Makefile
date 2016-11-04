PWD = `pwd`

all: run clean

run:
	su - raghav -c "cd ${PWD}; make -f rpm.mk hello_world.pkg"
	rpm -iv ${PWD}/RPM/RPMS/i386/hello_world-1.01-1.i386.rpm
	rpm -qa | grep -i hello_world

clean: 
	-rpm -e hello_world-1.01-1.i386
	@make -f rpm.mk clean
	rm -f /tmp/ex1
