
pthread_create() ... constructor API for thread .. similar to fork()
pthread_join()	 ... one of the destructor API's
pthread_exit()	 ... another destructor API for threads

pthread_self()	 ... get my thead-id
pthread_equal()  ... compare two thread-ids

variables on stack vs static variables

pthread_kill()	 ... send a signal to a thread

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
