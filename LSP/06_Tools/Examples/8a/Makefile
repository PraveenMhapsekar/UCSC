PWD = `pwd`

all: run clean

run:
	su - raghav -c "cd ${PWD}; make -f rpm.mk mysh.pkg"
	rpm -iv ${PWD}/RPM/RPMS/i386/mysh-1.01-1.i386.rpm
	rpm -qa | grep -i mysh
	rpm -e mysh-1.01-1.i386

clean: 
	-rpm -e mysh-1.01-1.i386
	@make -f rpm.mk clean
	rm -f /tmp/ex1
