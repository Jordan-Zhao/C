/*1-6.c程序：把输入的数字作为函数自变量，算出它的sin值*/
#include<stdio.h>				/*文件预处理，包含标准输入输出库*/
#include<math.h>             		/*文件预处理，包含数学函数库*/
int main()                  		/*C程序的主函数，开始入口*/
{
	double a,b;
	printf("请输入自变量:");
	scanf("%lf",&a);
	b=sin(a);                   	/*调用数学函数计算*/
	printf("sin(%lf)=%lf\n",a,b);
}
