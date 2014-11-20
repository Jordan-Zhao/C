/*4-14.c程序：读取系统目录文件“/etc/rc.d”中所有的目录结构*/
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>

int main()
{
	DIR * dir;
	struct dirent * ptr;
	int i;
	dir=opendir("/etc/rc.d");
	while((ptr = readdir(dir))!=NULL)
	{
		printf("目录: %s\n",ptr->d_name);
	}
	closedir(dir);
}
