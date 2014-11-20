/*7-2.c程序：父进程向子进程发出信号，结束子进程*/
#include<stdio.h>		/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>	    	/*文件预处理，包含system、exit等函数库*/
#include<signal.h>      	/*文件预处理，包含kill、raise等函数库*/
#include<sys/types.h>  	/*文件预处理，包含waitpid、kill、raise等函数库*/
#include<sys/wait.h>    	/*文件预处理，包含waitpid函数库*/
#include<unistd.h>     	/*文件预处理，包含进程控制函数库*/

int main ()             	/*C程序的主函数，开始入口*/
{ 
	pid_t result;
	int ret;
	result=fork();         /*调用fork函数，复制进程,返回值存在变量result中*/
	int newret;
	if(result<0) /*通过result的值来判断fork函数的返回情况，这儿进行出错处理*/
	{
			perror("创建子进程失败");
			exit(1);
	}
	else if (result==0)  	/*返回值为0代表子进程*/
	{
			raise(SIGSTOP); 	/*调用raise函数，发送SIGSTOP 使子进程暂停*/
			exit(0);
	}
	else                    	/*返回值大于0代表父进程*/
	{
			printf("子进程的进程号(PID)是：%d\n",result);
			if((waitpid(result,NULL,WNOHANG))==0)
			{
				if(ret=kill(result,SIGKILL)==0)
 			/*调用kill函数，发送SIGKILL信号结束子进程result */
				printf("用kill函数返回值是：%d，发出的SIGKILL信号结束的进程进程号：%d\n",ret,result);
				else{ perror("kill函数结束子进程失败");}
			}
	}
}
