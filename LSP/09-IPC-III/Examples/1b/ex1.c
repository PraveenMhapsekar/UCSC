// sourced from
// http://www.lainoox.com/checking-endianness-of-your-operating-system/
#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int x = 1;
		fprintf(stderr, "%s Endian\n",((*(char *)&x == 1)?"Little":"Big"));
 
    return 0;
}
