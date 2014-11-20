/*6-6.c程序：避免子进程成为僵尸进程*/  
#include<stdio.h>			/*文件预处理，包含标准输入输出库*/
#include<unistd.h>           	/*文件预处理，包含fork函数库*/
#include<sys/types.h>       	/*文件预处理，包含fork、wait、waitpid函数库*/
#include<sys/wait.h>        	/*文件预处理，包含wait、waitpid函数库*/

int main ()                  	/*C程序的主函数，开始入口*/
{
	pid_t pid,wpid;
	int status,i;
	pid=fork();          		/*调用fork函数复制进程，返回值存在变量pid中*/
	if(pid==0)
	{
			printf("这是子进程,进程号(pid)是:%d\n",getpid());
			sleep(5);        	/*子进程等待5秒钟*/
			exit(6);
	}
	else
	{
			printf("这是父进程,正在等待子进程……\n");
			wpid=wait(&status);    	/*父进程调用wait函数，消除僵尸进程*/
			i=WEXITSTATUS(status);	/*通过整形指针status,取得子进程退出时的状态*/
			printf("等待的进程的进程号(pid)是:%d ,结束状态:%d\n",wpid,i);
	}
}
