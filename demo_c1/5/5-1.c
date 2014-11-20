#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>

int main()
{
	int fd;
	fd=open("/dev/ttyS0",O_RDWR|O_NOCTTY| O_NONBLOCK);
	/* O_RDWR读写模式。O_NOCTTY标志告诉linux系统,这个程序不会成为对应这个端口的控制终端,如果没有指定这个标志,那么任何一个输入,诸如键盘中止信号等,都将会影响你的进程。O_NONBLOCK标志告诉linux系统这个程序以非阻塞的方式打开。 */

	if(fd==-1)
	   perror("open error\n");
	else 
	   printf("open success\n");
	return(fd); 
}
