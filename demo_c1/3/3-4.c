#include "stdio.h"
#include <ctype.h>

main()
{
	char c;   
	while((c=getchar())!='\n')
		if(isupper(c)) 
			printf("%c is an uppercase character\n",c);
}
