/*7-8.c程序：进程利用消息队列通信*/  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>

struct msgmbuf                   	/*结构体，定义消息的结构*/
    {
    long msg_type;                	/*消息类型*/
    char msg_text[512];         	/*消息内容*/
    };

int main()
{
	int qid;
	key_t key;
	int len;
	struct msgmbuf msg;
	if((key=ftok(".",'a'))==-1)   /*调用ftok函数，产生标准的key*/
	{
		perror("产生标准key出错");
		exit(1);
	}
	if((qid=msgget(key,IPC_CREAT|0666))==-1)/*调用msgget函数，创建、打开消息队列*/
	{
		perror("创建消息队列出错");
		exit(1);
	}
	printf("创建、打开的队列号是：%d\n",qid);  /*打印输出队列号*/
	puts("请输入要加入队列的消息：");
	if((fgets((&msg)->msg_text,512,stdin))==NULL)/*输入的消息存入变量msg_text*/
	{
		puts("没有消息");
		exit(1);
	}
	msg.msg_type=getpid();
	len=strlen(msg.msg_text);
	if((msgsnd(qid,&msg,len,0))<0)  /*调用msgsnd函数，添加消息到消息队列*/
	{
		perror("添加消息出错");
		exit(1);
	}
	if((msgrcv(qid,&msg,512,0,0))<0)  /*调用msgrcv函数，从消息队列读取消息*/
	{
		perror("读取消息出错");
		exit(1);
	}
	printf("读取的消息是：%s\n",(&msg)->msg_text); /*打印输出消息内容*/
	if((msgctl(qid,IPC_RMID,NULL))<0)/*调用msgctl函数，删除系统中的消息队列*/
	{
		perror("删除消息队列出错");
		exit(1);
	}
	exit (0);
}
