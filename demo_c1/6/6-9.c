/*6-9.c程序：守护进程和它的子进程退出信息写入系统日志文件*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<syslog.h>
#include <signal.h> 
#include <sys/param.h> 
#include <sys/stat.h> 

int main()
{
	pid_t child1,child2; 
	int i; 
	child1=fork();
	if(child1>0)        			/*(1)创建子进程，终止父进程*/
		exit(0);        			/*这是第一子进程，后台继续执行*/
	else if(child1< 0) 
	{
		perror("创建子进程失败");	/*fork失败，退出*/
		exit(1);
	}
	setsid();               		/*(2)在子进程中创建新会话*/
	chdir("/");             		/*(3)改变工作目录到“/”*/ 
	umask(0);               		/*(4)重设文件创建掩码*/
	for(i=0;i< NOFILE;++i)  		/*(5)关闭文件描述符*/ 
		close(i); 
	openlog("例6-9程序信息",LOG_PID,LOG_DAEMON);/* 调用openlog,打开日志文件*/
	child2=fork();
	if(child2==-1)
	{
		perror("创建子进程失败");	/*fork失败，退出*/
		exit(1);
	}
	else if(child2==0)
	{
		syslog(LOG_INFO,"第二子进程暂停5秒！"); /* 调用syslog，写入系统日志*/
		sleep(5);              /*睡眠5秒钟*/
		syslog(LOG_INFO,"第二子进程结束运行。");/* 调用syslog，写入系统日志*/
		exit(0);
	}
	else     /* 返回值大于0代表父进程，这是第二子进程的父进程，即第一子进程*/
	{
		waitpid(child2,NULL,0); /*第一子进程调用waitpid函数，等待第二子进程*/
		syslog(LOG_INFO, "第一子进程在等待第二子进程结束后，也结束运行。");
		closelog();         	   /*调用closelog，关闭日志服务*/
		while(1)              	   /*无限循环*/
		{
			sleep(10);      	   /*睡眠10秒钟*/
		}
	}
}
