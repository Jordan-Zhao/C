/*6-8.c程序：主程序每隔一分钟向/tmp目录中的日志6-8.log报告运行状态*/
#include <stdio.h>				/*文件预处理，包含标准输入输出库*/
#include <time.h>                	/*文件预处理，包含时间函数库*/

void init_daemon(void);        	/*守护进程初始化函数*/ 

int main()                       	/*C程序的主函数，开始入口*/
{ 
	FILE *fp; 
	time_t t; 
	init_daemon();  				/*初始化为daemon*/ 
	while(1)                       		/*无限循环,每隔10秒钟向6-8.log写入运行状态*/
	{ 
		sleep(10);                     	/*睡眠10秒钟*/ 
		if((fp=fopen("6-8.log","a+")) >=0)/*打开6-8.log文件,若没有此文件,创建它*/
		{ 
			t=time(0); 
			fprintf(fp,"守护进程还在运行，时间是： %s",asctime(localtime(&t)) ); 
			fclose(fp); 
		} 
	} 
}
