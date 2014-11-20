/*7-3.c程序：用户按下中断键(Ctrl+C)时的自定义信号处理函数设计 */  
#include<stdio.h>			/*文件预处理，包含标准输入输出库*/
#include<signal.h>        	/*文件预处理，包含signal等函数库*/
#include<unistd.h>        	/*文件预处理，包含进程控制函数库*/

void fun_ctrl_c();         	/*自定义信号处理函数声明*/

int main ()                 	/*C程序的主函数，开始入口*/
{
	(void) signal(SIGINT,fun_ctrl_c);/*如果按了Ctrl+C键,调用fun_ctrl_c函数*/
	printf("主程序：程序进入一个无限循环！\n");
	while(1)
	{
		printf("这是一个无限循环(要退出请按Ctrl+C键)！\n");
		sleep(3);
	}
	exit(0);
}

void fun_ctrl_c()          	/*自定义信号处理函数*/
{
	printf("\t你按了 Ctrl+C 哦:)\n");
	printf("\t信号处理函数：有什么要处理，在处理函数中编程！\n");
	printf("\t此例不处理，重新恢复SIGINT信号的系统默认处理。\n");
	(void) signal(SIGINT,SIG_DFL);   /*重新恢复SIGINT信号的系统默认处理*/
}
