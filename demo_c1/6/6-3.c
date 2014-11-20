/*6-3.c程序：测试到LUPA社区的网络连通状况*/  
#include<stdio.h>				/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>              	/*文件预处理，包含system函数库*/

int main ()                      	/*C程序的主函数，开始入口*/
{ 
	int newret;
	printf("系统分配的进程号(PID)是：%d\n",getpid());   /*显示输出进程号*/
	newret=system("ping www.lupaworld.com"); /*调用ping程序，创建新进程*/
	return 0;
}
