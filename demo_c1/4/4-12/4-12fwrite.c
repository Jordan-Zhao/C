/*4-12fwrite.c程序：把帐号信息写入文件*/  
#include<stdio.h>
#define set_s(x,y,z) {strcpy(s[x].name,y);s[x].pay=z;}   /*自定义宏，用于赋值*/
#define nmemb 3

struct test                     	/*定义结构体*/
{
	char name[20];
	int pay;
}s[nmemb];

int main()
{
	FILE * fp;                   	/*定义文件变量指针*/
	set_s(0,"张三",12345);
	set_s(1,"李四",200);
	set_s(2,"王五",50000);
	fp=fopen("4-12file","a+");	/*打开(创建)文件*/
	fwrite(s,sizeof(struct test),nmemb,fp);/*调用fwite函数把块信息写入文件*/
	fclose(fp);
	return  0;                    	/*关闭文件流*/
}
