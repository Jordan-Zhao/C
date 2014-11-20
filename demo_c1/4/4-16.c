/*4-16.c程序： 为“/etc/passwd”文件建立硬链接“4-16link”*/
/* */
#include<unistd.h>
int main()
{
	link("/etc/passwd","4-16link");
	system("ls 4-16link -l");
	system("ls /etc/passwd -l");
}
