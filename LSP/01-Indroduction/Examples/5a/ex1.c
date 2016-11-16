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
  //          ^     ^     ^     ^     ^     ^     ^     ^     ^     ^
  /*   traverse recursively to end of above string, and then 
       print the immediately prior alphabet/letter 
       of the above indicated locations in reverse order. */

  fn(str);
  putchar('\n');
  return 0;
}

