#include<stdlib.h>

int main( )
{  
  char *p;
  if((p = getenv("USER")))
    printf("USER=%s\n",p);
  return 0;
}
