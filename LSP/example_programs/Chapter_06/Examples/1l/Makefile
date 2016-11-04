all: prep run clean

prep:
	@echo "This is Lane 2." > ./ex.dat
	@echo "This also is lbne 1." >> ./ex.dat
	@echo "this is Laane 1." >> ./ex.dat
	@echo "This is Labne 1." >> ./ex.dat
	@echo "This is Lbne 1." >> ./ex.dat
	@echo "This is Lcne 1." >> ./ex.dat
	@echo "this is Ldne 1." >> ./ex.dat
	@echo "This is Lene 1." >> ./ex.dat
	@echo "This is Lfne 1." >> ./ex.dat
	@echo "" >> ./ex.dat
	@echo " " >> ./ex.dat
	@echo "  " >> ./ex.dat
	
run: ex.sh
	./ex.sh 2>&1 | less

clean:
	@rm -f ./ex.dat
