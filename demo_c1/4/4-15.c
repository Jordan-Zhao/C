/*4-15.c程序： 为“/etc/passwd”文件建立软链接“4-15link”*/
#include<unistd.h>

int main()
{
	symlink("/etc/passwd","4-15link");
	system("ls 4-15link -l");
	system("ls /etc/passwd -l");
}
