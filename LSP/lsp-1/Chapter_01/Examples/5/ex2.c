#include <stdio.h>
#include <string.h>

void fn(char *);

void fn(char *str) {
	static int i;

	printf("Loop #%d\n",++i);

  if (*str) {
      fn(str+6);
      putchar(*str-1);
  }
  return;
}

int main(void) {
  /* Some, World Currencies */
  char *str="\"YeN! cEnT! pEsO! KrOnEr! pEnCe! LeMpIrA! pUlS! Hi!!\" ";

	int len;

	printf("Hello World!");
	len=strlen(str);
  fn(str);
  putchar('\n');
	// printf("Hello World!");
  return 0;
}

