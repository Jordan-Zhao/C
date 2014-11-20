#include<mysql/mysql.h>						/*mysql开发头文件*/
#include<stdio.h>							/*标准输入输出头文件*/
int main(){
		MYSQL com_10_6;							/*定义句柄*/
		MYSQL_RES *jg;							/*定义结果指针标识*/
		MYSQL_FIELD *zd;						/*定义字段指针标识*/
		MYSQL_ROW hs,hs1;
		unsigned long *changdu;					/*定义字段长度标识*/
		unsigned int zds;						/*定义字段数标识*/
		unsigned int xhl,dw;					
		mysql_init(&com_10_6);					/*初始化句柄*/
		if(!mysql_real_connect(&com_10_6,"localhost","root","","rsglxt",0,NULL,0))													/*判断是否能够连接到数据库*/
			printf("数据库连接失败:%s\n",mysql_error(&com_10_6));	
					/*当连接不到指定的数据库时，通过mysql_error()函数向终端报错*/
		else printf("数据库连接成功!\n");

        if(mysql_query(&com_10_6,"select * from employees"))
               /*SQL语句查询，不成功则由mysql_error()函数报错*/
			     fprintf(stderr,"查询失败:%s\n",mysql_error(&com_10_6));
		   else
		   {			
			jg=mysql_store_result(&com_10_6);
			mysql_data_seek(jg,2);				/*将当前记录指针往后跳两条*/
			hs1=mysql_fetch_row(jg);			/*检索下一行记录*/
			printf("记录跳至第%s行!\n",hs1[0]);	/*显示检索到的行数*/
     		
			dw=mysql_field_seek(jg,2);			/*将记录指针跳到第二列*/
			printf("%u\n",dw);
			
			printf("employees表的字段如下:\n");	
        	while(zd=mysql_fetch_field(jg))
			{									/*返回一个所有字段结构的数组*/
				if(zd!= NULL)					/*判断该数组不为空*/
					printf("%s\n",zd ->name);	/*输入各字段名*/
				else
					break;		
			}
        	printf("表中各字段的长度如下:\n");
			hs=mysql_fetch_row(jg);				/*检索下一行记录*/
			if(hs)
			{   
				zds=mysql_num_fields(jg);		/*检测列数*/
				changdu=mysql_fetch_lengths(jg);	/*检测当前行中所有列的长度*/
				for(xhl=0;xhl<zds;xhl++)
				{   /*输入当前列号，及该列定义的长度*/
					printf("第%u个字段有%lu个字节长度.\n",xhl+1,changdu[xhl]);
				}
			}
		}
		mysql_free_result(jg);						/*释放结果集合分配的内存*/
		
		mysql_close(&com_10_6);						/*关闭本次连接*/
}
