// page 14 example #4

// #define ENV_VAR	"TERM"
#define ENV_VAR	"PARM"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	int i=0;
	char *var;

	var=getenv(ENV_VAR);

	printf("%s=%s\n",ENV_VAR,var);

	exit(0);

}
