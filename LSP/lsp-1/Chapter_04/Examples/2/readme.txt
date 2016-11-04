TOPICS:
1.   construction/teardown of threads
2.   thread attributes
3.   concurrency control - semaphore / mutex, spin lock
4.   advanced topics for concurrency management





CREATION
pthread_create() ... constructor API for thread .. similar to fork()

TERMINATION
pthread_join()	 ... one of the destructor API's
pthread_exit()	 ... a thread exiting itself. another destructor API for threads
pthread_kill()	 ... send a signal to a thread
pthread_cancel() ... allows a thread to cancel another thread.

return           ... behaves like pthread_exit
exit()           ... should NOT be called by any thread - because it terminates the PID

THREAD ID
pthread_self()	 ... get my thread-id
pthread_equal()  ... compare two thread-ids

variables on stack vs static variables


pthread_attr_init()
pthread_attr_setdetachstate()

SCHEDULER
- SCHED_FIFO		(RT)	 		100
- SCHED_RR			(RT)
- SCHED_OTHER   (TS)			 40 having nice values -20 thru 19
- SCHED_BATCH   (TS)
- SCHED_IDLE    (really low priority)

pthread_setschedprio()
pthread_setschedparam()

pthread_yield()

pthread_mutex_lock()
pthread_mutex_unlock()
