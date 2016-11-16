fd=3
fd=4
fd=5
fd=6
fd=7
fd=8
fd=9
fd=10
fd=11
fd=12
fd=13
fd=14


For a process, therefore, IO to the devices underlying the fd's,
can be handled

a)  Sequentially. (Blocked Mode)
    Note that a process blocks on a read by default; therefore, a process will block for each fd before proceeding to the next fd.
    that is, till such time that prior fd's are complete, IO using a given fd cannot be attempted.

	  the disadvantage to this approach is that a process may spend an indeterminate amount of time awaiting data from the underlying device, even though there are devices associated with the higher fd's that are ready for IO.

b)  Sequentially. (NonBlocked Mode)
	
		Using the O_NONBLOCK flag to open(), blocking api's to an fd can then return immediately.

	  the process can then check each fd in a polling loop, and cycle back once the last fd is checked.

    The benefit to this approach is that the indeterminate latencies for handling IO are mitigated to a great extent.

	  The disadvantage to this approach is that the CPU and system resources are constantly active.
	  
c)  interrupt-driven - (again, NonBlocked Mode)

		A better approach is to use an interrupt driven mechanism, that 
   i)  puts the process into a blocked state for the time that *no* IO is possible on any fd
	ii)  unblocks the process, and continue processing, once an 'fd' is available for IO.

