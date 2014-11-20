/*2-6-main.c程序：从三道题目中随机抽取一道*/  
#include "shuiji.h"	/*文件预处理，包含自定义fun_shuiji函数的声明和一些库函数*/

int main()           	/*C程序的主函数，开始入口*/
{
	int n;
	static char str[3][80]={"Linux c的函数都可以分割为独立的文件吗?","make工程管理器的作用是?","makefile文件是否可以使用变量?"};
	n=fun_shuiji();	/*调用fun_shuiji函数，把随机数返回给变量n*/
	printf("随机抽取的题号是:%d\n",n+1);
	printf("第%d题:",n+1);
	puts(str[n]);
}
