#define m 70
#include<stdio.h>
#include <stdlib.h>

int compar (const void *a ,const void *b)
{
	int *aa=(int * ) a,*bb = (int * )b;
	if( * aa >* bb)return 1;
	if( * aa == * bb) return 0;
	if( * aa < *bb) return -1;
}

main( )
{
	int base[m],n ;
	int i;
	printf("input n(n<50)\n");
	scanf("%d",&n); 
	printf("\n");
	qsort(base,n,sizeof(int),compar);
	for(i=0;i<n;i++)
		printf("%d  ",base[i]);
	printf("\n");
}
