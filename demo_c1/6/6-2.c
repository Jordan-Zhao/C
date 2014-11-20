/*6-2.c程序：创建一个新进程, 新进程的进程号和原程序的进程号相同*/  
#include<stdio.h>				/*文件预处理，包含标准输入输出库*/
#include<unistd.h>              	/*文件预处理，包含getpid、getppid函数库*/

int main ()                       	/*C程序的主函数，开始入口*/
{ 
	char *args[]={"/usr/bin/vim",NULL};
	printf("系统分配的进程号(PID)是：%d\n",getpid());      /*显示输出进程号*/
	if(execve("/usr/bin/vim",args,NULL)<0)     /*调用vim程序，创建新进程*/
	perror("用execve创建进程出错");
	return 1;
}
