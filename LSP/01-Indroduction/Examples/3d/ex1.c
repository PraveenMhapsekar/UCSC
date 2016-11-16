#include <stdio.h>

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

	return 0;

}

void fn1() {
	int a=0;
	
	printf("value in fn1 for 'a' is '%d'.\n", ++a);

}

void fn2() {
	int a=0;
	
	printf("value in fn2 for 'a' is '%d'.\n", ++a);

}
	
	
