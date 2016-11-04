fn := "myfile.txt"

all: run clean

run:
	touch ${fn}
#
	@chmod 4755 ${fn}; ls -l ${fn}
	@chmod 2755 ${fn}; ls -l ${fn}
	@chmod 1755 ${fn}; ls -l ${fn}
	@chmod 6755 ${fn}; ls -l ${fn}
	@chmod 6644 ${fn}; ls -l ${fn}
	@chmod 7000 ${fn}; ls -l ${fn}
#
	@echo "=> on this note: observe dir permissions of /tmp"
	ls -ld /tmp
	@echo "=> note the \"t\" in the permissions of /tmp. what does it do?"
	ls -ld /usr/bin/passwd /etc/passwd
	@echo "=> note the \"s\" in the permissions of /usr/bin/passwd. what does it do?"
#
	
clean:
	rm -f myfile.txt
