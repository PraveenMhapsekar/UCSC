PKG = hello_world
PKGVER = 1.01

RPM_BUILD_DIR = `pwd`/RPM/
RPM_SPECS_DIR = `pwd`/RPM/SPECS

all: ${PKG}.pkg clean

${PKG}.pkg: 
	# Step #1: Create Build Environment
	mkdir -p ${RPM_BUILD_DIR}tmp \
			${RPM_BUILD_DIR}BUILD \
		  ${RPM_BUILD_DIR}RPMS/i386 \
			${RPM_BUILD_DIR}RPMS/i686 \
			${RPM_BUILD_DIR}RPMS/noarch \
			${RPM_BUILD_DIR}SOURCES \
	    ${RPM_BUILD_DIR}SPECS \
			${RPM_BUILD_DIR}SRPMS
	# Step #2: define .. some build env variables
	echo “%_topdir	${RPM_BUILD_DIR}” >> \
			${RPM_BUILD_DIR}.rpmmacros
	echo “%_tmppath	${RPM_BUILD_DIR}tmp” 	>> \
			${RPM_BUILD_DIR}.rpmmacros
	# Step #3 .. Spec file 	
	echo "%define _topdir		`pwd`/RPM/" > ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%define name	${PKG}" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%define release		1" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%define version		1.01" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%define buildroot %{_topdir}/%{name}-%{version}-%{root}" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "BuildRoot: %{buildroot}" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "Summary: ${PKG}" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "Name: ${PKG}" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "Version: %{version}" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "Release: %{release}" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "Source: %{name}-%{version}.tar.gz" >> \
		${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "License: GPL" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "Group: Development/Tools" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%description" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "The ${PKG} program is my first CLI program." >> \
		${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%prep" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "make clean" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%build" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "make build" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "make" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%install" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "make install" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%files" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "%defattr(-,root,root)" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	echo "/tmp/ex1" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	# echo "%doc /usr/local/info/${PKG}.info" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	# echo "%doc %attr(0444,root,root) /usr/local/man/man1/${PKG}.1"  >>  ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	# echo "%doc COPYING AUTHORS README NEWS" >> ${RPM_BUILD_DIR}SPECS/${PKG}-1.spec
	# Step #4 .. Copy Source
	cp ex1.c ${RPM_BUILD_DIR}SOURCES
	cp ex1.mk ${RPM_BUILD_DIR}BUILD/Makefile
	# Step #5 .. BUILD	
	cd ${RPM_BUILD_DIR}; rpmbuild -v -bb --clean SPECS/hello_world-1.spec
	# Step #6 .. Verify	
	rpm -Vp RPM/RPMS/i386/hello_world-1.01-1.i386.rpm

clean:
	rm -fr ${RPM_BUILD_DIR} ex?
