CFLAGS="-g"
LDFLAGS="-lpthread"
DIR="$(shell pwd)"
j=1

all: run clean
	-@make clean >/dev/null 2>&1

run: ex1 
	-./ex1 &
	ps -C ex1 -L -o pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:25,comm
	wait
	-./ex1 -mf10 -ar20 -i e &
	ps -C ex1 -L -o pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:25,comm


ex1: ex1.c

clean:
	rm -fr ex1 
