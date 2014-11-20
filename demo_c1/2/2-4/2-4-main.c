/*2-4-main.c程序：比较输出最大值*/
#include  <stdio.h>	             		/*文件预处理，包含标准输入输出库*/
#include <max.h>                    	/*文件预处理，包含自定义函数的声明*/

int main ()                         	/*C程序的主函数，开始入口*/
{ 
	int i,j,k;
	printf("请输入第一个整数：");
	scanf("%d",&i);
	printf("请输入第二个整数：");
	scanf("%d",&j);
	k=max(i,j);             		/*调用max函数，返回值传递给k*/
	printf("最大值是：%d\n",k);
	return 0;
}
