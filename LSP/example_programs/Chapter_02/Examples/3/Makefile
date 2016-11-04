fn := "myfile.txt"

all: run clean

run:
	touch ${fn}
	@chmod 000 ${fn}; ls -l ${fn}
	@chmod 400 ${fn}; ls -l ${fn}
	@chmod 200 ${fn}; ls -l ${fn}
	@chmod 100 ${fn}; ls -l ${fn}
	@chmod 700 ${fn}; ls -l ${fn}
	@chmod 710 ${fn}; ls -l ${fn}
	@chmod 750 ${fn}; ls -l ${fn}
	@chmod 755 ${fn}; ls -l ${fn}

clean:
	rm -f myfile.txt


