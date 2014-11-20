/*4-6.c程序：如果存在“/home/4-6file”文件，以只读方式打开，如果不存在，创建文件*/
#include<stdio.h>			/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>        	/*文件预处理，包含system函数库*/
#include<fcntl.h>         	/*文件预处理，包含open函数库*/

int main ()                 	/*C程序的主函数，开始入口*/
{
	int fd;
	if((fd=open("/home/4-6file",O_CREAT|O_TRUNC|O_WRONLY,0600))<0)
	{   /*选项O_TRUNC表示文件存在时清空*/
		perror("打开文件出错");
		exit(1);
	}
	else
	{
		printf("打开(创建)文件\"4-6file\"，文件描述符为：%d\n",fd);
	}
	if(close(fd)<0)
	{
		perror("关闭文件出错");
		exit(1);
	}
	system("ls /home/4-6file -l");
	return 0;
}
