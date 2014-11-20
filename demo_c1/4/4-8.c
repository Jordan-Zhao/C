/*4-8.c程序：打开“/home/4-8file”后对其加上强制性的写入锁，然后释放写入锁*/
#include<stdio.h>				/*文件预处理，包含标准输入输出库*/
#include<stdlib.h>             	/*文件预处理，包含system函数库*/
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

void lock_set(int fd, int type)
{
	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len =0;
	while(1){
		lock.l_type = type;
		if((fcntl(fd,F_SETLK,&lock))==0){/*根据不同的type值给文件上锁或解锁*/
		if( lock.l_type == F_RDLCK )   /*F_RDLCK为共享锁*/
			printf("加上读取锁的是： %d\n",getpid());
		else if( lock.l_type == F_WRLCK )  /*F_WRLCK为排斥锁*/
			printf("加上写入锁的是： %d\n",getpid());
		else if( lock.l_type == F_UNLCK )
			printf("释放强制性锁： %d\n",getpid());
		return;
		}
		fcntl(fd, F_GETLK,&lock);
		if(lock.l_type != F_UNLCK){
			if( lock.l_type == F_RDLCK ) 
				printf("加上读取锁的是： %d\n",lock.l_pid);
			else if( lock.l_type == F_WRLCK )
				printf("加上写入锁的是： %d\n",lock.l_pid);
		getchar();
		}
	}
}

int main ()                       /*C程序的主函数，开始入口*/
{
	int fd;
	fd=open("/home/4-8file",O_RDWR | O_CREAT, 0666);
	if(fd < 0){
		perror("打开出错");
		exit(1);
	}
	lock_set(fd, F_WRLCK);
	getchar();
	lock_set(fd, F_UNLCK);
	getchar();
	close(fd);
	exit(0);
}
