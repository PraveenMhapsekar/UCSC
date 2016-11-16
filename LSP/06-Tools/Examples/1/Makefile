all: prep run clean

prep:
	@echo "This is Line 1." > ./ex.dat
	@echo "This also is line 1." >> ./ex.dat
	@echo "This is Line 1, line 1. 2times" >> ./ex.dat
	@echo "This is Line 1, line 1, Line 1. 3times" >> ./ex.dat
	@echo "This is Line 1, line 1, Line 1,Line 1. 4times" >> ./ex.dat
	@echo "This is Line 1, line 1, Line 1,Line 1, Line 1. 5times" >> ./ex.dat
	@echo "This is Line 1, Line 2." >> ./ex.dat
	@echo "This is Line 1, Line 2, Line 3." >> ./ex.dat
	@echo "This is Line 1, Line 2, Line 3, Line 4." >> ./ex.dat
	
run: ex.sh
	./ex.sh

clean:
	@rm -f ./ex.dat
