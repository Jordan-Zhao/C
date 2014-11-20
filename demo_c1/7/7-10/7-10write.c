/*7-10write.c程序：系统V共享内存写入端*/  
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
	char temp;
	people *p_map;
	char* name = "/dev/shm/myshm2";
	key = ftok(name,0);                 /*调用ftok函数，产生标准的key*/
	shm_id=shmget(key,4096,IPC_CREAT);/*调用shmget函数，获取共享内存区域的ID*/
	if(shm_id==-1)
	{
		perror("获取共享内存区域的ID 出错");
		return;
	}
	p_map=(people*)shmat(shm_id,NULL,0);/* 调用shmat函数，映射共享内存*/
	temp='a';
	for(i = 0;i<10;i++)
	{
		temp+=1;
		memcpy((*(p_map+i)).name,&temp,1);
		(*(p_map+i)).age=20+i;
	}
	if(shmdt(p_map)==-1)      /*调用shmdt函数，解除进程对共享内存区域的映射*/
		perror("解除映射出错");
}
