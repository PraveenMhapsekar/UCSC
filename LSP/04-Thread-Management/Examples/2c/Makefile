EX1:=ex3

all: run clean

LDFLAGS="-lpthread"

run: $(EX1)
	-./$(EX1) &
	ps -mL
	ps -C $(EX1) -L -o pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:25,comm

$(EX1): $(EX1).c

clean:
	rm -f ex?
