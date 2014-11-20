/*4-9.c程序：用fopen函数打开文件“4-9file”*/  
#include<stdio.h>

int main()
{
	FILE * fp;                                 		/*定义文件变量指针*/
	if((fp=fopen("4-9file","a+"))==NULL)       	/*打开(创建)文件*/
	{
		printf("打开(创建)文件出错");          		/*出错处理*/
		exit(0);
	}
	fclose(fp);                                 		/*关闭文件流*/
}
