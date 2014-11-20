#include "stdio.h"

int main()
{
	int n,t,m;
	float a=2,b=1,s=0;
	scanf("%d",&m);
	for(n=1;n<=m;n++){
		s=s+a/b;
		t=a;         /*这部分是程序的关键，请读者猜猜t的作用*/
		a=a+b;
		b=t;
	}
	printf("sum is %9.6f\n",s);
}
