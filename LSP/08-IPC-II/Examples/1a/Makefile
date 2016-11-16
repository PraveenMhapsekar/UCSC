all: run runall run_negativetests clean

run: ex1
	./ex1
	./ex1 -a
	./ex1 -b
	./ex1 -c "Hello!"
	./ex1 -d "Hello, Again!"
	./ex1 -0
	./ex1 -1
	./ex1 -2

runall: ex1
	./ex1 -a -b -c "Hello!" -d "Hello, Again!" -012

run_negativetests:
	./ex1 -?
	./ex1 -h
	./ex1 -c
	./ex1 -a -b -c "Hello!" -d "Hello, Again!" -0 -1 -2 -h

clean:
	@rm -f ./ex1 
