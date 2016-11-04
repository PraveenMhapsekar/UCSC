#include <stdio.h>
#include <string.h>

#define STR "\"YeN! cEnT! pEsO! KrOnEr! pEnCe! LeMpIrA! pUlS! Hi!!\""

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
	char str[100];
	memset(str,0,100);

	strcpy(str,STR);
	str[strlen(STR)]=0;

	int len;


	len=strlen(str);
	printf("Hello World!");
  fn(str);
  putchar('\n');
  return 0;
}

