/*7-4.c程序：先阻塞用户发出的中断信号，程序主体运行完毕后才进入自定义信号处理函数 */  
#include<stdio.h>	 		/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>	         	/*文件预处理，包含进程控制函数库*/
#include<signal.h>          	/*文件预处理，包含进程通信函数库*/
#include<sys/types.h>     	/*文件预处理，包含进程控制函数库*/ 
#include<unistd.h>         	/*文件预处理，包含进程控制函数库*/

void fun_ctrl_c();         	/*自定义信号处理函数声明*/

int main ()                 	/*C程序的主函数，开始入口*/
{
	int i;
	sigset_t set,pendset;
	struct sigaction action;
	(void) signal(SIGINT,fun_ctrl_c);	/*调用fun_ctrl_c函数*/
	if(sigemptyset(&set)<0)            	/*初始化信号集合*/
		perror("初始化信号集合错误");
	if(sigaddset(&set,SIGINT)<0)      	/*把SIGINT信号加入信号集合*/
		perror("加入信号集合错误");
	if(sigprocmask(SIG_BLOCK,&set,NULL)<0)/*把信号集合加入到当前进程的阻塞集合中*/
		perror("往信号阻塞集增加一个信号集合错误");
	else
	{
		for(i=0;i<5;i++)
		{
			printf("显示此文字，表示程序处于阻塞信号状态！\n");
			sleep(2);
		}
	}
	if(sigprocmask(SIG_UNBLOCK,&set,NULL)<0)/*当前的阻塞集中删除一个信号集合*/
		perror("从信号阻塞集删除一个信号集合错误");
}

void fun_ctrl_c()          /*自定义信号处理函数*/
{
	printf("\t你按了Ctrl+C 系统是不是很长时间没理你？\n");
	printf("\t信号处理函数：有什么要处理，在处理函数中编程！\n");
	printf("\t此例不处理，直接结束!\n");
	(void) signal(SIGINT,SIG_DFL);      /*重新恢复SIGINT信号的系统默认处理*/
}
