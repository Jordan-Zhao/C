/*4-10.c程序：把键盘上输入的字符写入文件“4-10file”*/  
#include<stdio.h>

int main()
{
	FILE * fp;                               	/*定义文件变量指针*/
	char ch;
	if((fp=fopen("4-10file","a+"))==NULL)	/*打开(创建)文件*/
	{
		printf("打开(创建)文件出错");    		/*出错处理*/
		exit(0);
	}
	printf("请输入要写入文件的一个字符：");		/*提示输入一个字符*/
	fputc((ch=fgetc(stdin)),fp);			/*把键盘输入的一个字符写入文件*/
	fclose(fp);                            		/*关闭文件流*/
}
