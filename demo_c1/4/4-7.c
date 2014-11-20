/*4-7.c程序：复制“/etc/passwd”文件*/  
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{
	int fdsrc,fddes,nbytes;
	int flags=O_CREAT | O_TRUNC | O_WRONLY;
	int z;
	char buf[20], des[20];
	printf("请输入目标文件名:");			/*提示输入目标文件名*/
	scanf("%s",des);                 		/*读入目标文件名*/
	fdsrc=open("/etc/passwd",O_RDONLY);	/*只读方式打开源文件*/
	if(fdsrc<0)
	{
		exit(1);
	}
	fddes=open(des,flags,0644);         	/*打开目标文件的权限为：644*/
	if(fddes<0)
	{
		exit(1);
	}
	while((nbytes=read(fdsrc,buf,20))>0)
	{
		z=write(fddes,buf,nbytes);
		if(z<0)
		{
			perror("写目标文件出错");/*此函数可以用来输出“错误原因信息”字符串*/
		}
	}
	close(fddes);
	close(fdsrc);
	printf("复制\"/etc/passwd\"文件为\"%s\"文件成功！\n",des);
	exit(0);
}
