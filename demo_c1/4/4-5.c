/*4-5.c程序：在“/home”目录下创建一个名称为“4-5file”的文件*/  
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd;
	fd=creat("/home/4-5file",S_IRUSR); /*所有者具有只读权限 */
	system("ls /home/4-5file -l");/*调用system函数执行命令ls显示此文件的信息 */
	return 0;
}
