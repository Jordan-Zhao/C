#include "ctype.h"
#include "stdio.h"
int main( )
{
  char c;
  int i;
  for( ;(c=getchar())!='\n';)
      if(isxdigit(c)) 
        printf("%c is a hexadecimal digits\n",c);
  return 0;
}
