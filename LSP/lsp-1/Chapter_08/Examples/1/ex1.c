#include <stdio.h>

int main(int argc, char **argv) {

	while (*++argv) {
		printf("you entered: %s\n",*argv);

	}
}

