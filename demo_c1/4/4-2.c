/*4-2.c 设置“/etc/passwd”文件权限*/
#include<sys/types.h>		/*文件预处理，包含chmod函数库*/
#include<sys/stat.h>       	/*文件预处理，包含chmod函数库*/

int main ()                  	/*C程序的主函数，开始入口*/
{
	chmod("/etc/passwd",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	return 0;/*S_IRUSR表示拥有者具有读权限，S_IRGRP表示组内人具有读权限，S_IROTH表示其他人具有读权限*/
}
