#include <stdio.h>
#include <sys/types.h>
#include<fcntl.h>
#include <termios.h>
#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"

int main()
{
	int fd,c=0,res;
	struct termios oldtio, newtio;
	char buf[256];
	printf("start ...\n");
	fd=open(MODEMDEVICE,O_RDWR | O_NOCTTY);/*打开PC的COM2端口*/
	if(fd<0)
	{
		perror(MODEMDEVICE);
		exit(1);
	}
	printf("open...\n");
	tcgetattr(fd,&oldtio);/*将目前终端机参数保存至oldtio(它是个结构体)*/
	bzero(&newtio,sizeof(newtio));/*清除newtio(它也是个结构体)*/
	newtio.c_cflag=BAUDRATE |CS8 |CLOCAL|CREAD;
	newtio.c_iflag=IGNPAR;
	newtio.c_oflag=0;
	newtio.c_lflag=ICANON;/*设置为正规模式*/
	tcflush(fd,TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);/*新的termios作为通信端口的参数*/
	printf("reading...\n");
	while(1)
	{
		res=read(fd,buf,255);
		buf[res]=0;
		printf("res=%d vuf=%s\n",res,buf);
		if(buf[0]=='@') break;
	}
	printf("close...\n");
	close(fd);
	tcsetattr(fd,TCSANOW,&oldtio);/*恢复旧的端口参数*/
	return 0;
}
