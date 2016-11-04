EX1:=ex1

all: run clean

LDFLAGS="-lpthread"

run: $(EX1)
	## Watch here ex1 is an orphan, because the subshell has exited. 
	./$(EX1) &  
	ps -f
	ps -mL
	ps -C $(EX1) -L -o pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:25,comm

$(EX1): $(EX1).c

clean:
	rm -f ex?
