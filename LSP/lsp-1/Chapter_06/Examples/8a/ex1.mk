all: build clean

build:
	make -C ../SOURCES ex1
	mkdir -p ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386/tmp/
	cp ../SOURCES/ex1 ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386/tmp/

install:
	mkdir -p ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386/tmp/
	cp ../SOURCES/ex1 ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386/tmp/
	cp ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386/tmp/ex1 /tmp
	ls -latr /tmp/ex1

clean: 
	-rm -f ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386/tmp/*
	-rmdir ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386/tmp/
	-rmdir ${HOME}/rpmbuild/BUILDROOT/mysh-1.01-1.i386
	-cd ${HOME}/rpmbuild; rmdir BUILDROOT BUILD  RPMS  SOURCES  SPECS  SRPMS
	-rmdir ${HOME}/rpmbuild/
	rm -f ex1 /tmp/ex1
