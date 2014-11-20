/*7-6.c程序：管道的创建和读写*/  
#include<stdio.h>	/*文件预处理，包含标准输入输出库*/

int main ()	/*C程序的主函数，开始入口*/
{ 
	FILE *fp;
	int num;
	char buf[500];
	memset(buf,0,sizeof(buf)); /*把buf所指的内存区域的前sizeof(buf)得到的字节置为0，初始化清空的操作*/
	printf("建立管道……\n");
	fp=popen("ls -l","r");   /*调用popen函数，建立管道(读管道)*/
	if(fp!=NULL)
	{
			num=fread(buf,sizeof(char),500,fp);
			if(num>0)
			{
				printf("第一个命令是“ls–l”，运行结果如下：\n");
				printf("%s\n",buf);
			}
			pclose(fp);
	}
	else
	{
			printf("用popen创建管道错误\n");
			return 1;
	}
	fp=popen("grep 7-6","w");   /*调用popen函数，建立管道(写管道)*/
	printf("第二个命令是“grep 7-6”，运行结果如下：\n");
	fwrite(buf,sizeof(char),500,fp);
	pclose(fp);
	return 0;
}
