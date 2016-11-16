#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	int i;

	for (;*env;env++)
		printf("%s\n", *env);

}
