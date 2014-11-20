/*2-6-fun_shuiji.c程序：fun_shuiji函数的定义*/
#include "shuiji.h"			/*文件预处理，自定义fun_shuiji函数的声明和一些库函数*/

int fun_shuiji()      		/*自定义函数，生成一个0至2的随机数*/
{
	srand(time(NULL));
	int a;
	a=(rand()%3);
	return a;
}
