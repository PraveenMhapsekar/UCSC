// ch5_12.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

// subroutine function  ... uses longjmp()
extern void fn1 (void);
 
// StackFrame to save "context info"
static jmp_buf Buf;  // to store return context

int var=0;

int main() {

   int res=0;

	 // Step: #1
   fprintf(stderr,"sizeof(buf)=%d\n",sizeof(Buf));

   // Step: #2: change Global Variable value
	 var=5;
   // Step: #3: saves context/stack info in Buf
	 // Step: #7: return into the context of setjmp()
   if ((res=setjmp(Buf)) == 0) {
   	fprintf(stderr,"setjmp(==%d)..returning once (var==%d)!\n",res,var);
		// Step: #4: Invoke function.
   	fn1();
   }
   else {
	// Step: #8: exit here  ... 
	// setjmp() returns as a result of calling longjmp() 
		fprintf(stderr,"setjmp(==%d) ..returned twice!..(var==%d)!\n",res,var);
		exit(0);
   }

	// Code is never reached!
	fprintf(stderr, "Hello World!\n");

}

void fn1(void) {
	
	// Step: 5:  Change Global Variable value, again
	var=6;

	// Step: #6: Invoke longjmp
	// ok .. we get to call longjmp()
	// a longjmp implements a NON-LOCAL goto ... 
	longjmp(Buf,5);
	// longjmp(Buf,2);
	// longjmp(Buf,1);
	// longjmp(Buf,0);

	// Code is never reached!
	fprintf(stderr, "Hello World!\n");

}

/***  OUTPUT
$ make ch5_11                ## compile 
gcc    -o ch5_11 ch5_11.c

$ ./ch5_11                ## run #1
setjmp..returning once!
setjmp..returning twice!
*/
