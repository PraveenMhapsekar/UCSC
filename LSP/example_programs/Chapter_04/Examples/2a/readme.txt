/* 
 * http://docs.oracle.com/cd/E19963-01/html/821-1601/tlib-1.html#tlib-12602
 * Finishing Up
 * A thread can terminate its execution in the following ways:
 * -   By returning from its first (outermost) procedure, 
 *     the threads start routine.  (see ex1.c)
 * -   By calling pthread_exit(), supplying an exit rc. (see ex2.c)
 * -   By termination with POSIX cancel functions. See pthread_cancel().  
 *     (see ex3.c)
 *     The default behavior of a thread is to linger until some other thread has acknowledged its demise by “joining” with the lingering thread. This behavior is the same as the default pthread_create() attribute that is nondetached, see pthread_detach. The result of the join is that the joining thread picks up the exit rc of the terminated thread and the terminated thread vanishes.
 *
 *     An important special case arises when the initial thread, calling main(), returns from calling main() or calls exit(). This action causes the entire process to be terminated, along with all its threads. So, take care to ensure that the initial thread does not return from main() prematurely.
 *
 *     Note that when the main thread merely calls pthread_exit, the main thread terminates itself only. The other threads in the process, as well as the process, continue to exist. The process terminates when all threads terminate.

