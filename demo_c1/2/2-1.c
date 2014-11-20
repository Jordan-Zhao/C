/*2-1.c程序：在屏幕上打印输出五行文字*/  
#include  <stdio.h>					/*文件预处理，包含标准输入输出库*/
int output()						/*自己定义函数，利用printf输出字符串*/
{
	printf("Linux程序设计，有点意思！\n");
	return 0;
}

int main ()							/*C程序的主函数，开始入口*/
{ 
	int i;
	for(i=0;i<5;i++)
		output();
    return 0;
}
