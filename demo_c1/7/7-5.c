/*7-5.c程序：管道的创建和读写*/  
#include<stdio.h>	 	/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>	    	/*文件预处理，包含system、exit等函数库*/
#include<sys/types.h>  	/*文件预处理，包含waitpid、kill、raise等函数库*/ 
#include<sys/wait.h>  	/*文件预处理，包含waitpid函数库*/
#include<unistd.h>    	/*文件预处理，包含进程控制函数库*/

int main ()             	/*C程序的主函数，开始入口*/
{ 
	pid_t result;
	int r_num;
	int pipe_fd[2];
	char buf_r[100];
	memset(buf_r,0,sizeof(buf_r)); /*把buf_r所指的内存区域的前sizeof(buf_r)得到的字节置为0，初始化清空的操作*/
	if(pipe(pipe_fd)<0)     /*调用pipe函数，创建一个管道*/
	{
			printf("创建管道失败");
			return -1;
	}
	result=fork();         /*调用fork函数，复制进程,返回值存在变量result中*/
	if(result<0) /*通过result的值来判断fork函数的返回情况，这儿进行出错处理*/
	{
			perror("创建子进程失败");
			exit;
	}
	else if (result==0)           /*返回值为0代表子进程*/
	{
			close(pipe_fd[1]);
			if((r_num=read(pipe_fd[0],buf_r,100))>0)
				printf("子进程从管道读取%d个字符，读取的字符串是：%s\n",r_num,buf_r);
			close(pipe_fd[0]);
			exit(0);
	}
	else                           /*返回值大于0代表父进程*/
	{
				close(pipe_fd[0]);
				if(write(pipe_fd[1], "第一串文字",10)!=-1)
					printf("父进程向管道写入“第一串文字”!\n");
				if(write(pipe_fd[1], "第二串文字",10)!=-1)
					printf("父进程向管道写入“第二串文字”!\n");
				close(pipe_fd[1]);
				waitpid(result,NULL,0);//调用waitpid, 阻塞父进程,等待子进程退出
				exit(0);
	}
}
