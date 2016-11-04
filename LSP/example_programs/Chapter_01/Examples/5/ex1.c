#include <stdio.h>

void fn(char *str) {
  if (*str) {
      fn(str+6);
      putchar(*str-1);
  }
  return;
}

int main(void) {
  /* Some, World Currencies */
  char *str="\"YeN! cEnT! pEsO! KrOnEr! pEnCe! LeMpIrA! pUlS! Hi!!\"";

  fn(str);
  putchar('\n');
  return 0;
}

