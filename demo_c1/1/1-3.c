/*1-3.c程序：求和程序*/ 
#include  <stdio.h>				/*文件预处理，包含标准输入输出库*/
int main ()						/*C程序的主函数，开始入口*/
{ 
		int a,b,sum;
		printf("请输入第一个数:\n");	/*在屏幕上打印输出"请输入第一个数:"并等待输入*/
		scanf("%d",&a);
		printf("请输入第二个数:\n");	/*在屏幕上打印输出"请输入第二个数:"并等待输入*/
		scanf("%d",&b);
		sum=a+b;                    	/*求和*/
		printf("两数之和是:%d\n",sum);/*输出和*/
 	return 0;
}
