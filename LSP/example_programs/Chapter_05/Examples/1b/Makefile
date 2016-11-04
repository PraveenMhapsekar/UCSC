all: run clean

run: ex1
	#  run "ulimit -c unlimited" - if no core file is generated.
	nohup longrunningjob.sh &
	sleep 4
	## -/bin/kill -s SIGINT `pgrep "ex1"`
	-kill -1 `ps -eaf | egrep "longrunningjob|ex1" | awk '{print $$2}'`
	# -kill -9 `ps -eaf | egrep "longrunningjob|ex1" | awk '{print $$2}'`
	# -kill -41 `ps -eaf | egrep "longrunningjob|ex1" | awk '{print $$2}'`
	# -kill -11 `ps -eaf | egrep "longrunningjob|ex1" | awk '{print $$2}'`

ex1: ex1.c

clean:
	rm -f ex? *.out core.*
