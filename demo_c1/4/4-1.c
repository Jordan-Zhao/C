/*4-1.c程序：列出当前目录下和系统特定目录下的文件信息*/  
#include<stdio.h>	                	/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>                  	/*文件预处理，包含system函数库*/

int main ()                         	/*C程序的主函数，开始入口*/
{ 
	int newret;
	printf("列出当前目录下的文件信息：\n"); 
	newret=system("ls -l");        	/*调用ls程序，列出当前目录下的文件信息*/
	printf("列出\"dev/sda1\"的文件信息：\n"); 
	newret=system("ls /dev/sda1 -l");		/*列出“/dev/sda1”的文件信息*/
	printf("列出\"dev/ lp0\"的文件信息：\n"); 
	newret=system("ls /dev/lp0 -l");      	/*列出“/dev/ lp0”的文件信息*/
	return 0;
}
