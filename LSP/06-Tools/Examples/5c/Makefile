# PARM1:="Universe"
PARM1="Universe"

all: run clean

run: ex1
	# ./ex1; echo $$;
	PARM1="Galaxy" ./ex1.sh; echo $$;
	(PARM1=${PARM1} ./ex1.sh; echo $$ )
	PARM1="Globe" ./ex1; echo $$;

ex1: ex1.c ex1.h
	(gcc -o ex1 ex1.c; echo $$;) 
	# (ps -f; gcc -o ex1 ex1.c; echo $$; ps -f ) 

clean:
	rm -f ex1
