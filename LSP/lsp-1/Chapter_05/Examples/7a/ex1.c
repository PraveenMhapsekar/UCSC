// ch5_12.c

#define ALARMTMOUT 10
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

	 int n=ALARMTMOUT;

   int res=0;

   fprintf(stderr,"sizeof(buf)=%d\n",sizeof(Buf));


	 alarm(n);
   // saves stack info in Buf
	 var=5;
   if ((res=sigsetjmp(Buf,1)) == 0) {
   	fprintf(stderr,"sigsetjmp..returning once (var==%d)!\n",var);
   	fn1();
   }
   else {

	// setjmp() returns as a result of 
	//    calling longjmp() 
	fprintf(stderr,"sigsetjmp..return twice!..returned value %d (var==%d)!\n",res,var);
	exit(0);
   }

// Code is never reached!
fprintf(stderr, "Hello World!\n");

}

void fn1(void) {

	var=6;

	// ok .. we get to call longjmp()
	siglongjmp(Buf,3);
	// siglongjmp(Buf,2);
	// siglongjmp(Buf,1);
	// siglongjmp(Buf,0);

	// Code is never reached!
	fprintf(stderr, "Hello World!\n");

}
