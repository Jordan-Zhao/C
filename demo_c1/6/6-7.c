/*6-7.c程序：父进程运行比子进程快，避免子进程成为僵尸进程*/  
#include<stdio.h>	        	/*文件预处理，包含标准输入输出库*/
#include<unistd.h>          	/*文件预处理，包含fork函数库*/
#include<sys/types.h>		/*文件预处理，包含fork、wait、waitpid函数库*/
#include<sys/wait.h>       	/*文件预处理，包含wait、waitpid函数库*/

void display0();            	/*子程序声明*/
void display1();
void display2();

int main ()              		/*程序的主函数，开始入口*/
{ 
	pid_t result;
	int status,select,num;
	void (*fun[3])();		/*利用函数指针建立三个子程序*/
	fun[0]=display0;
	fun[1]=display1;
	fun[2]=display2;
	printf("1.复制进程\n2.不复制进程\n请输入您的选择:");
	scanf("%d",&select);
	if(select==1)			/*如果用户输入1，复制进程*/
	{
			result=fork();		/*调用fork函数复制进程，返回值存在变量result中*/
			if(result==-1)
			{
				perror("复制进程出错");
				exit(1);
			}
	}
	if (result==0)          /*子进程*/
	{
			printf("这是子进程(进程号：%d，父进程号：%d): ",getpid(),getppid());
			printf("进入思科(Cisco)1912交换机开机界面。\n ");
			printf("1 user(s) now active on Management Console.\n");
			printf("\tUser Interface Menu\n");
			printf("\t[0] Menus\n");
			printf("\t[1] Command Line\n");
			printf("\t[2] IP Configuration\n");
			printf("Enter Selection：");
			scanf("%d",&num);             /*运用函数指针，运行相应的子程序*/
			if(num>=0&&num<=2)
				(*fun[num])();
			exit(0);
	}
	else
	{
			waitpid(result,&status,0); /*父进程调用waitpid函数，消除僵尸进程*/
			printf("这是父进程(进程号：%d，父进程号：%d)\n ",getpid(),getppid());
			if(WIFEXITED(status)==0)
				printf("子进程非正常终止，子进程终止状态：%d\n", WIFEXITED(status));
			else
				printf("子进程正常终止，子进程终止状态：%d\n", WIFEXITED(status));
			exit(0);
	}
}

void display0()                   /*子程序部分*/
{
	printf("您选择进入了菜单模式\n");
}

void display1()
{
	printf("您选择进入了命令行模式\n");
}

void display2()
{
	printf("您选择进入了IP地址配置模式\n");
}
