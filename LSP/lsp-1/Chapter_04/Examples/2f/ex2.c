#include <stdio.h>

int fn1() {
	static int a=0;

	printf("fn1.a=%d\n",a++);
}
	
int fn2() {
	static int a=1000;

	printf("fn2.a=%d\n",a++);
}

int main() {
	fn1();		// calling function1
	fn1();		// calling function1, again
	fn2();		// calling function2
	fn1();		// function1
	fn2();
	fn2();
	fn2();
	fn1();
}
