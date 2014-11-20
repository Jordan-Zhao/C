/*1-9.c程序：判断并输出两个输入整数的最小数*/
#include <stdio.h>						/*文件预处理，包含标准输入输出库*/
int min(int x, int y);                  	/*自定义函数说明*/
int main()                             		/*C程序的主函数，开始入口*/
{
	int a1,a2,min_int;                    	/*定义三个变量*/
	printf("请输入第一个整数：");
	scanf("%d",&a1);                      		/*输入的值赋值给变量a1*/
	printf("请输入第二个整数：");
	scanf("%d",&a2);                      		/*输入的值赋值给变量a2*/
	min_int=min(a1,a2); /*调用函数min，返回的最小值赋值给变量min_int*/
	printf("最小的整数是：%d\n",min_int); 	/*输出最小的整数*/ 
}

int min(int x, int y)         			/*自定义函数：比较后返回最小值*/
{
		if (x<y)
			return x;
		else
			return y;
}
