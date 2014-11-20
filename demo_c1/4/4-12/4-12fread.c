/*4-12fread.c程序：把帐号信息写入文件*/  
#include<stdio.h>
#define nmemb 3

struct test						/*定义结构体*/
{
	char name[20];
	int pay;
}s[nmemb];

int main( )
{
	FILE * fp;              		/*定义文件变量指针*/
	int i;
	fp = fopen("4-12file", "r");	/*打开文件*/
	fread(s,sizeof(struct test),nmemb,fp);/*调用fread函数从文件读取块信息*/
	fclose(fp);                  			  /*关闭文件流*/
	for(i=0;i<nmemb;i++)
		printf("帐号[%d]:%-20s余额[%d]:%d\n",i,s[i].name,i,s[i].pay);
	return 0;
}
