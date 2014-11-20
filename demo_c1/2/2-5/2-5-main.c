/*2-5-main.c程序：计算学生的总成绩和平均成绩*/  
#include  <stdio.h>	        	/*文件预处理，包含标准输入输出库*/
#include "chengji.h"        	/*文件预处理，包含fun_avg和fun_sum函数声明*/

int main ()                  	/*C程序的主函数，开始入口*/
{ 
	int n,i;
	float average,sum;
	printf("请输入需要统计的学生数：");
	scanf("%d",&n);
	int array[n];
	for(i=0;i<n;i++)
	{
		printf("请输入第%d个学生的成绩：",i+1);
		scanf("%d",&array[i]);
	}
	sum=fun_sum(array,n);	/*调用avg函数，返回值传递给average*/
	printf("输入的%d个学生的总成绩：%6.2f\n",n,sum);
	average=fun_avg(array,n);	/*调用avg函数，返回值传递给average*/
	printf("输入的%d个学生的平均成绩是：%6.2f\n",n,average);
}
