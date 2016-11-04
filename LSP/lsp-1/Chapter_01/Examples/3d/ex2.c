#include <stdio.h>

int a=50;

void fn1(void);
void fn2(void);

int main() {
	fn1();	
	fn1();	
	fn2();	
	fn2();	
	fn2();	
	fn1();	
	fn2();	
	fn1();	
	printf("value in main for 'a' is '%d'.\n", a);
	return 0;
}

void fn1() {
	static int a=0;
	printf("value in fn1 for 'a' is '%d'.\n", ++a);

}

void fn2() {
	static int a=10;
	printf("value in fn2 for 'a' is '%d'.\n", ++a);
}
