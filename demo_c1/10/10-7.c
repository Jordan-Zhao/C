#include<stdio.h>							/*标准输入输出头文件*/
#include<mysql/mysql.h>						/*mysql开发头文件*/
int main()
{	
		MYSQL com_10_7;							/*定义句柄*/
		MYSQL_RES *jg;							/*用于存放记录列数*/
		MYSQL_ROW hs;							/*用于存放记录行数*/
		int xht;								/*循环变量*/
		ulong * changdu;						/*用于存放当前行中每列的长度变量*/
		
		uint xhi,zds;							/*用于存放列数的变量*/
		char cx[4096];							/*查询语句数组*/
		
		/*插入数据*/
		const char *depname[]={"总经理办公室","人事部","市场部","技术部","财务部","开发部","网管中心","远程办事处","后勤部"};			/*depname字段的内容*/
		const char *depms[]={"zb","rs","sc","js","cw","kf","wgzx","ycbsc", "hq"};
		/*depms字段的内容*/
		uint ls=sizeof(depname)/sizeof(char *);   	/*行数变量*/
		/*查询语句定义*/
		/*创建名为depinfo的数据表，含有depname和depms两个字段*/
		const char *query_create="create table depinfo(depID int(2) NOT NULL AUTO_INCREMENT,depname varchar(20),depms varchar(50),primary key(depID))";
		/*向表中分别插入这两个字段的内容*/
		const char *query_insert="insert into depinfo (depname,depms) values (\"%s\",\"%s\")";
		/*删除depinfo表中所有depID小于3的记录*/
		const char *query_delete="delete from depinfo where depID<=3";
		/*更新depinfo表中depID=5的另外两项*/
		const char *query_update="update depinfo set depname='科研部',depms='ky' where depID=5";
		/*删除depinfo表*/
		const char *query_drop="drop table depinfo";
		/*查看depinfo表中的内容*/
		const char *query_select="select * from depinfo";
		
		/*初始化连接结构*/
		if(!mysql_init(&com_10_7))
			/*初始化不成功，显示相应信息，并退出*/
			fprintf(stderr,"无法初始化MYSQL结构!\n");
		else printf("初始化成功!\n");	/*成功则显示相应信息*/
		
		/*连接数据库*/
		if(!mysql_real_connect(&com_10_7,"localhost","root","","rsglxt",0, NULL,0))   /*连接不成功，显示错误代码及相关信息，并退出*/
		fprintf(stderr,"%d: %s\n",mysql_errno(&com_10_7),mysql_error(&com_10_7));
		else	printf("连接数据库成功!\n");		/*成功则显示相应信息*/
		
		/*创建表*/
		if(mysql_query(&com_10_7,query_create))/*mysql_query()函数执行SQL语句*/
		{		
			/*查询失败，显示错误代码及相关信息*/
			fprintf(stderr,"无法创建表!\n%d: %s\n", mysql_errno(&com_10_7), mysql_error(&com_10_7));
			mysql_close(&com_10_7);			/*关闭本次连接后退出*/	
		}
		else printf("表创建成功!\n");				
/*成功则显示相关信息*/

		/*插入记录*/
		for(xhi=0;xhi<ls;xhi++)              		/*在实际的行数内进行循环*/
		{
			sprintf(cx,query_insert,depname[xhi],depms[xhi]);    
			/*sprintf方式实现对记录的插入*/
			if(mysql_query(&com_10_7,cx))  /*执行SQL语句*/
			{
				/*查询失败，显示错误代码及相关信息*/
				fprintf(stderr,"无法插入记录!\n%s\n%d: %s\n",cx, mysql_errno (&com_10_7),mysql_error(&com_10_7));
				mysql_close(&com_10_7);			/*关闭本次连接后退出*/	
			}
			printf("插入%d条记录\n",mysql_affected_rows(&com_10_7));
			/*提示有几行已经插入*/
		}

		/*删除记录*/
		if(mysql_query(&com_10_7,query_delete))	/*执行SQL语句*/
		{
			/*查询失败，显示错误代码及相关信息*/
			fprintf(stderr,"无法删除记录!\n%d:%s\n", mysql_errno (&com_10_7), mysql_error(&com_10_7));
			mysql_close(&com_10_7);/*关闭本次连接后退出*/
		}
		printf("%d条记录被删除\n",mysql_affected_rows(&com_10_7));
		/*更新记录*/
		if(mysql_query(&com_10_7,query_update))
		{
			/*查询失败，显示错误代码及相关信息*/
			fprintf(stderr,"无法更新记录!\n%d:%s\n", mysql_errno(&com_10_7), mysql_error(&com_10_7));
			mysql_close(&com_10_7);/*关闭本次连接后退出*/
		}
		printf("%d条记录被更新\n",mysql_affected_rows(&com_10_7));

		/*显示记录*/
		printf("经过插入,更新,删除后的数据记录为:\n");
		if(mysql_query(&com_10_7,query_select))  /*执行查询语句*/
		{
			fprintf(stderr,"无法显示记录!\n%d:%s\n", mysql_errno(&com_10_7), mysql_error(&com_10_7));/*查询失败，显示错误代码及相关信息*/
			mysql_close(&com_10_7);/*关闭本次连接后退出*/
		}
		else
		{
			jg=mysql_store_result(&com_10_7);  	/*将查询结果拖到内部缓冲中*/
			zds=mysql_num_fields(jg);    		/*存放列数*/
			while(hs=mysql_fetch_row(jg))		/*检索一个结果的下一行*/
			{
				changdu=mysql_fetch_lengths(jg);/*记录当前行的列长度*/
				for(xht=0;xht<zds;xht++)		/*以列数为限，进行循环*/
				{
					printf("%s ",hs[xht]);		/*输出记录中的各列内容*/
				}	
				printf("\n");
			}
        	printf("\n");
		}
		
		/*删除表*/

		//if(mysql_query(&com_10_7,query_drop))/*执行查询语句*/
		//{
			/*查询失败，显示错误代码及相关信息*/
		//fprintf(stderr,"无法删除表!\n%d:%s\n", mysql_errno (&com_10_7), mysql_error(&com_10_7));
		//	mysql_close(&com_10_7);/*关闭本次连接后退出*/
		//}
		
		/*关闭本次连接*/
		mysql_close(&com_10_7);
}
