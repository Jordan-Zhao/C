#include<stdlib.h>

int main()
{
	char * p;
	if((p=getenv("USER")))
	printf("USER =%s\n",p);
	setenv("USER","test",1);
	printf("USER=%s\n",getenv("USER"));
	unsetenv("USER");
	printf("USER=%s\n",getenv("USER"));
	return 1;
}
