/*6-5.c程序：用exit和_exit函数终止进程的区别*/  
#include<stdio.h>			/*文件预处理，包含标准输入输出库*/
#include<unistd.h>         	/*文件预处理，包含fork函数库*/
#include<sys/types.h>     	/*文件预处理，包含fork函数库*/

int main ()                  	/*C程序的主函数，开始入口*/
{ 
	pid_t result;
	result=fork();           	/*调用fork函数，返回值存在变量result中*/
	if(result==-1) /*通过result的值来判断fork函数的返回情况，这儿先进行出错处理*/
	{
			perror("创建子进程失败");
			exit(0);
	}
	else if (result==0)     	/*返回值为0代表子进程*/
	{
			printf("测试终止进程的_exit函数!\n");
			printf("这一行我们用缓存!");
			_exit(0);
	}
	else                    	/*返回值大于0代表父进程*/
	{
			printf("测试终止进程的exit函数!\n");
			printf("这一行我们用缓存!");
			exit(0);
	}
}
