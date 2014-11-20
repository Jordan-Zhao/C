#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	mode_t new_umask,old_umask;
	new_umask=0266;
	old_umask=umask(new_umask);
	printf("系统原来的权限掩码：%o\n",old_umask);
	printf("系统新的权限掩码：%o\n",new_umask);
	system("touch liu6");
	printf("创建了新文件溜liu6");
	system("ls liu6 -l");
	return 0;
}
