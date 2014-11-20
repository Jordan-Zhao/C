#include<mysql/mysql.h>						/*mysql开发头文件*/
#include<stdio.h>							/*标准输入输出头文件*/
int main()	
{
MYSQL com_10_2;                                	/**定义mysql的句柄*/
mysql_init(&com_10_2);                       	/*初始化句柄*/
if(!mysql_real_connect(&com_10_2,"localhost","root","","rsglxt",0,NULL,0))
												/*判断是否能够连接到数据库*/
		fprintf(stderr,"连接数据库失败: %s\n",mysql_error(&com_10_2));
         /*当连接不到指定的数据库时，通过mysql_error()函数向终端报错*/
else printf("数据库连接成功!\n"); /*成功连接则在终端中显示相应信息*/
mysql_close(&com_10_2);  					/*关闭一个以前打开的连接*/
}
