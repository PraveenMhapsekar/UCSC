all: run1 run2 run3

run1:
	@echo "##########"
	@echo "Test Case #1: Shell Local Variable. "
	@echo "Note PARM value not displayed"
	PARM="Hello" 
	./echo.sh
	@echo "##########"

run2:
	@echo "##########"
	@echo "Test Case #2: Shell Environment Variable. "
	@echo "Note PARM value IS displayed"
	export PARM="Hello"; ./echo.sh
	# ./echo.sh
	@echo "##########"

run3:
	@echo "##########"
	./echo.sh
	@echo "Test Case #3: Shell Environment Variable (#2). "
	@echo "Note PARM value IS displayed"
	PARM="Hello" ./echo.sh
	@echo "##########"

clean:
	rm -f ex1
