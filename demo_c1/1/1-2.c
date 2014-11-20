/*1-2.c程序：百分制换算成五级制*/  
#include  <stdio.h>				/*文件预处理，包含标准输入输出库*/
int main ()						/*C程序的主函数*/
{ 
		int score;
		printf("请输入成绩:");		/*在屏幕上打印输出"请输入成绩："并等待输入*/
		scanf("%d",&score);			/*接收输入的成绩，赋值给变量score*/
		if (score>=90)				/*用输入的成绩判断等级并输出*/
			printf("优秀\n");
		else if (score>=80)
			printf("良好\n");
		else if (score>=70)
			printf("中等\n");
		else if (score>=60)
			printf("及格\n");
		else
			printf("不及格\n");
 	return 0;
}
