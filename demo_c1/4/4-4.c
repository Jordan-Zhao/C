/*4-4.c 获取“/etc/passwd”文件的大小*/
#include<stdio.h>
#include<unistd.h>		/*文件预处理，包含chmod函数库*/
#include<sys/stat.h>     	/*文件预处理，包含chmod函数库*/

int main ()                 	/*C程序的主函数，开始入口*/
{
	struct stat buf;
	stat("/etc/passwd",&buf);
	printf("\"/etc/passwd\"文件的大小是：%d\n最后一次访问时间是：%dl\n",buf.st_size,buf.st_atime);
	return 0;
}
