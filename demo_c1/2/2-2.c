/2-2.c程序：比较输出最大值*/  
#include  <stdio.h>	 				/*文件预处理，包含标准输入输出库*/
int max(int x,int y);             	/*自定义函数声明，也可以把声明放在main中*/
int main ()                        		/*C程序的主函数，开始入口*/
{ 
	int i,j,k;
	printf("请输入第一个整数：");
	scanf("%d",&i);
	printf("请输入第二个整数：");
	scanf("%d",&j);
	k=max(i,j);			/*调用max函数，返回值传递给k*/
	printf("最大值是：%d\n",k);
	return 0;
}

int max(int x,int y)	/*自定义函数，对传入的两个整数进程比较，输出最大值*/
{
	if(x>y)
		return x;
	else 
		return y;
}
