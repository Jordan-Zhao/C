/*7-9.c程序：匿名内存映射*/  
#include<sys/types.h>	/*文件预处理，包含waitpid、kill、raise等函数库*/ 
#include<unistd.h>     	/*文件预处理，包含进程控制函数库*/
#include <sys/mman.h>
#include <fcntl.h>

typedef struct     	/*结构体，定义一个people数据结构*/
{
	char name[4];
	int  age;
}people;

main(int argc, char** argv) 	/*C程序的主函数，开始入口*/
{ 
	pid_t result;
	int i;
	people *p_map;
	char temp;
	p_map=(people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);   	/*调用mmap函数，匿名内存映射*/
	result=fork();      	/*调用fork函数，复制进程,返回值存在变量result中*/
	if(result<0) /*通过result的值来判断fork函数的返回情况，这儿进行出错处理*/
	{
		perror("创建子进程失败");
		exit(0);
	}
	else if (result==0)	/*返回值为0代表子进程*/
	{
		sleep(2);
		for(i = 0;i<5;i++)
			printf("子进程读取: 第 %d 个人的年龄是： %d\n",i+1,(*(p_map+i)).age);
		(*p_map).age = 110;
		munmap(p_map,sizeof(people)*10); /*解除内存映射关系*/
		exit(0);
	}
	else              		/*返回值大于0代表父进程*/
	{
		temp = 'a';
		for(i = 0;i<5;i++)
		{
			temp += 1;
			memcpy((*(p_map+i)).name, &temp,2);
			(*(p_map+i)).age=20+i;
		}
		sleep(5);
		printf( "父进程读取: 五个人的年龄和是： %d\n",(*p_map).age );
		printf("解除内存映射……\n");
		munmap(p_map,sizeof(people)*10);
		printf("解除内存映射成功！\n");
	}
}
