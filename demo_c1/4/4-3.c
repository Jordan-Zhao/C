/*4-3.c 设置“/etc/passwd”文件权限*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	mode_t new_umask,old_umask;
	new_umask=0555;
	old_umask=umask(new_umask);
	printf("系统原来的权限掩码是：%o\n",old_umask);
	printf("系统新的权限掩码是：%o\n",new_umask);
	system("touch liu5");
	printf("创建了文件liu5\n");
	new_umask=0333;
	old_umask=umask(new_umask);
	printf("系统原来的权限掩码是：%o\n",old_umask);
	printf("系统新的权限掩码是：%o\n",new_umask);
	system("touch liu6");
	printf("创建了文件liu6\n");
	system("ls liu5 liu6 -l");
	return 0;
}
