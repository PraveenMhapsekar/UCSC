#include <stdio.h>

int main() {
	int a;

	/***    #1. try different locations for post-increment op  */
	a=5; printf("1a. %d+%d=%d\n", a++, a++, a + a);
	a=5; printf("1b. %d+%d=%d\n", a, a, a++ + a++);
	a=5; printf("1c. %d=%d+%d\n", a++ + a++, a, a);
	a=5; printf("1d. %d=%d+%d\n\n", a + a, a++, a++);

	/***    #2. try pre-incr op */
	a=5; printf("2a. %d+%d=%d\n", ++a, ++a, a + a);
	a=5; printf("2b. %d+%d=%d\n", a, a, ++a + ++a);
	a=5; printf("2c. %d=%d+%d\n", ++a + ++a, a, a);
	a=5; printf("2d. %d=%d+%d\n\n", a + a, ++a, ++a);

	/***    #3. try mix of post-incr op & pre-incr op */
	a=5; printf("3a. %d+%d=%d\n", ++a, a++, a + a);
	a=5; printf("3b. %d+%d=%d\n", a, a, ++a + a++);
	a=5; printf("3c. %d=%d+%d\n", ++a + a++, a, a);
	a=5; printf("3d. %d=%d+%d\n\n", a + a, ++a, a++);

	/***    #4. try another mix of post-incr op & pre-incr op */
	a=5; printf("4a. %d+%d=%d\n", a++, ++a, a + a);
	a=5; printf("4b. %d+%d=%d\n", a, a, a++ + ++a);
	a=5; printf("4c. %d=%d+%d\n", a++ + ++a, a, a);
	a=5; printf("4d. %d=%d+%d\n\n", a + a, a++, ++a);

	return 0;
}
