/*6-4.c程序：显示当前目录下的文件信息，并测试网络连通状况*/  
#include<stdio.h>	         	/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>           	/*文件预处理，包含system、exit等函数库*/
#include<unistd.h>     		/*文件预处理，包含fork、getpid、getppid函数库*/
#include<sys/types.h>     	/*文件预处理，包含fork函数库*/

int main ()                 		/*C程序的主函数，开始入口*/
{ 
	pid_t result;
	result=fork();         		/*调用fork函数，返回值存在变量result中*/
	int newret;
	if(result==-1) /*通过result的值来判断fork函数的返回情况，这儿先进行出错处理*/
	{
		perror("创建子进程失败");
		exit;
	}
	else if (result==0)			/*返回值为0代表子进程*/
	{
		printf("返回值是:%d,说明这是子进程!\n此进程的进程号(PID)是:%d\n此进程的父进程号(PPID)是:%d\n",result,getpid(),getppid());
		newret=system("ls -l");	/*调用ls程序，显示当前目录下的文件信息*/

	}
	else                         	/*返回值大于0代表父进程*/
	{
		sleep(10);
		printf("返回值是:%d,说明这是父进程!\n此进程的进程号(PID)是:%d\n此进程的父进程号(PPID)是:%d\n",result,getpid(),getppid());
		newret=system("ping www.lupaworld.com"); /*调用ping程序，测试网络连通*/
	}
}
