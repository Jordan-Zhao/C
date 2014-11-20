/*6-1.c程序：显示Linux系统分配的进程号（PID）和它的父进程号（PPID）*/  
#include<stdio.h>				/*文件预处理，包含标准输入输出库*/
#include<unistd.h>               	/*文件预处理，包含进程控制函数库*/
int main ()                       	/*C程序的主函数，开始入口*/
{ 
		printf("系统分配的进程号(PID)是：%d\n",getpid());    /*显示输出进程号*/
		printf("系统分配的父进程号(PPID)是：%d\n",getppid());/*显示输出父进程号*/
    	return 0;
}
