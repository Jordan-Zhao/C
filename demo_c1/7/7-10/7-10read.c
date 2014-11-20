/*7-10read.c程序：系统V共享内存读取端*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
 		char name[4];
 		int age;
} people;

main(int argc, char** argv)
{ 
	int shm_id,i;
	key_t key;
	people *p_map;
	char* name = "/dev/shm/myshm2";
	key = ftok(name,0); /*调用ftok函数，产生标准的key*/
	shm_id=shmget(key,4096,IPC_CREAT);/*调用shmget函数，获取共享内存区域的ID*/
	if(shm_id == -1)
	{
 		 perror("获取共享内存区域的ID 出错");
 		 return;
	}
	p_map = (people*)shmat(shm_id,NULL,0);
	for(i = 0;i<10;i++)
	{
 		printf( "姓名:%s\t",(*(p_map+i)).name );
 		printf( "年龄：%d\n",(*(p_map+i)).age );
	}
	if(shmdt(p_map) == -1) /*调用shmdt函数，解除进程对共享内存区域的映射*/
		perror("解除映射出错");
}
