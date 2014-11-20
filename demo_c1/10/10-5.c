#include<mysql/mysql.h>								/*mysql开发头文件*/
#include<stdio.h>									/*标准输入输出头文件*/

int main()
{
		MYSQL com_10_5;										/*定义句柄*/
mysql_init(&com_10_5);								/*初始化句柄*/
if(!mysql_real_connect(&com_10_5,"localhost","root","","",0,NULL,0))    												/*判断是否能够连接到数据库*/
		printf("连接数据库失败:%s\n",mysql_error(&com_10_5));
    			/*当连接不到指定的数据库时，通过mysql_error()函数向终端报错*/
else printf("连接数据库成功!\n");

if(mysql_create_db(&com_10_5,"exp")==0)
/*判断是否成功实现创建数据库，成功和失败都显示相关信息销误*/
		printf("数据库创建成功!\n");
else printf("创建数据库失败:%s\n",mysql_error(&com_10_5));

if(mysql_select_db(&com_10_5,"exp")==0)
/*判断是否成功实现选择数据库，成功则显示“数据库选择成功”,失败则显示相关错误*/
		printf("数据库选择成功!\n");
else printf("选择数据库失败:%s\n",mysql_error(&com_10_5));

mysql_close(&com_10_5);									/*关闭本次连接*/
}
