#include<stdio.h>									/*标准输入输出头文件*/
#include<mysql/mysql.h>								/*mysql开发头文件*/
int main()							
{
		MYSQL com_10_3;								/**定义mysql的句柄*/
char *cr ="insert into employees values ('0004','王西','男',24, '315246198312110548', '86428462','东','主任')"; /*用于实现插入的SQL语句*/
		mysql_init(&com_10_3);								/*初始化句柄*/
if(!mysql_real_connect(&com_10_3,"localhost","root","","rsglxt",0,NULL,0))
				fprintf(stderr," 连接数据库失败:%s\n",mysql_error(&com_10_3));
/*当连接不到指定的数据库时，通过mysql_error()函数向终端报错*/
		if(mysql_query(&com_10_3,cr))
			   fprintf(stderr,"查询失败:%s\n",mysql_error(&com_10_3));
			    /*判断能否查询，能则显示被更新的记录数，反之则显示不能查询的错误*/
		else printf("插入记录成功.\n",mysql_affected_rows(&com_10_3));
													/*成功则显示被更新的记录数*/
		mysql_close(&com_10_3);						/*关闭这次连接*/
}
