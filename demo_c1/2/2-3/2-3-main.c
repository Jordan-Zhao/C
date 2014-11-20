/*2-3-main.c程序：计算数组的平均值*/  
#include  <stdio.h>	          	/*文件预处理，包含标准输入输出库*/
float avg(int var[],int num); 	/*自定义函数，计算返回数组元素的平均值*/

int main ()                      	/*C程序的主函数，开始入口*/
{ 
	int n,i;
	float average;
	printf("请输入需要计算的整数个数：");
	scanf("%d",&n);
	int array[n];
	for(i=0;i<n;i++)
	{
		printf("请输入第%d个整数：",i+1);
		scanf("%d",&array[i]);
	}
	average=avg(array,n);		/*调用avg函数，返回值传递给average*/
	printf("所有%d个整数的平均值是：%6.2f\n",n,average);
}
