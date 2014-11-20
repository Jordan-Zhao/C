/*1-8.c程序：用于测试代码优化的复杂运算程序*/
#include <stdio.h>					/*文件预处理，包含标准输入输出库*/
int main(void)                      	/*C程序的主函数，开始入口*/
{
  double counter;                    	/*定义双精度实型变量*/
  double result; 
  double temp; 
  for (counter = 0; counter < 4000.0 * 4000.0 * 4000.0 / 20.0 + 2030;counter += (5 - 3 +2 + 1 ) / 4)			/*循环8亿多次，每次都有加减乘除运算*/
	   {
	   temp=counter/1239;
	   result=counter; 
	   }
	   printf("运算结果是：%lf\n", result); /*输出运算结果*/
}
