/*2-5-fun_avg.c程序：fun_avg函数的定义*/
float fun_avg(int var[],int num)	/*自定义函数，计算返回数组元素的平均值*/
{
	float avrg=0.0;
	int i;
	for(i=0;i<num;i++)
		avrg+=var[i];
	avrg/=num;
	return (avrg);
}
