#include <stdio.h>

// #define VARIABLE_CLASS auto
#define VARIABLE_CLASS static

void fn1(void) {
	VARIABLE_CLASS int a=0;
	printf("fn1.a==%d\n",a++);
}

void fn2(void) {
	VARIABLE_CLASS int a=0;
	printf("fn2.a==%d\n",a++);
}

int main() {
	fn1();
	fn1();
	fn1();
	fn2();
	fn1();
	fn2();
	fn2();
	fn2();
	fn1();
}
