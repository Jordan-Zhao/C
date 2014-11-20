#include<mysql/mysql.h>    /*mysql开发头文件*/
#include<stdio.h>          /*标准输入输出头文件*/

int main(){
		MYSQL com_10_4;   		/*定义mysql的句柄*/
		MYSQL_RES *ls;  		/*用于存放记录列数*/
		MYSQL_ROW hs;  			/*用于存放记录行数*/
		char *cxnr;   			/*用于存放SQL语句*/
		int xht;
		
		mysql_init(&com_10_4);  /*初始化句柄*/
		if(!mysql_real_connect(&com_10_4,"localhost","root","","rsglxt",0,NULL,0))/*判断是否能够连接到数据库*/
			printf("连接数据库失败:%s\n",mysql_error(&com_10_4));		/*当连接不到指定的数据库时，通过mysql_error()函数向终端报错*/
		else printf("连接数据库成功!\n"); 

		cxnr="select * from employees order by 'ID' asc";  /*定义SQL语句*/
		xht=mysql_real_query(&com_10_4,cxnr,(unsigned int)strlen(cxnr)); /*测得SQL语句的长度*/

		if(xht)  /*判决数据库中记录数*/
		{
			printf("查询失败:%s\n",mysql_error(&com_10_4));
		}
		else printf("查询成功!\n");
		ls=mysql_use_result(&com_10_4);
		while(hs=mysql_fetch_row(ls))    /*检索一个结果的下一行*/
		{
			for(xht=0;xht<mysql_num_fields(ls);xht++)/*mysql_num_fields()返回列的数量*/

			{
				printf("%s ",hs[xht]); 		/*输出记录中各列的内容*/
			}	
			 printf("\n");
		}
        	mysql_close(&com_10_4);   		/*关闭本次连接*/

}
