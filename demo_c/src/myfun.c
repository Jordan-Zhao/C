#include "myh.h"
int getA() {
	return 10;
}

int getB() {
	return 11;
}

void countInvoke() {
	static int c = 5;
	c++;
	printf("%d\n", c);
}

void printd(int n) {
	if (n < 0) {
		putchar(' ');
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}

void swap(int *a1, int *a2) {
	int tmp = *a1;
	*a1 = *a2;
	*a2 = tmp;
}

int strlen1(int *a) {
	int n = 0;
	//printf("%d --\n",*a);
	for (n = 0; *a != '\0'; a++) {
		printf("%d --\n", *a);
		n++;
	}
	printf("%d ++++++\n", n);
	return n;
}

int scanftest() {
	int y, m;
	char d[2];
	int n = scanf("%d-%d-%s", &y, &m, d);
	printf("%d result: %d/%d/%s \n", n, y, m, d);
	return n;
}

void filetest1() {
	char a = getc(stdin);
	putc(a, stderr);
}

void log1(char *msg) {
	FILE *f = fopen("E:/c.log", "a");
	while (*msg != '\0') {
		putc(*msg++, f);
	}
	putc('\n', f);
	fclose(f);
}

void systemtest() {
	system("date");
}

void outFileContent() {
	int fd = open("E:/c.log", O_RDONLY, 0);
	char content[100];
	int r = read(fd, content, 100);
	printf("%s \t %d \n", content, sizeof(content));
}

char *outArgs(int n, ...) {
	char r[1024] = "";
	char *t;

	va_list ap; /* points to each unnamed arg in turn */
	va_start(ap, n); /* make ap point to 1st unnamed arg */
	int i = 0;

	for (i = 0; i < n; i++) {
		t = va_arg(ap, char *);
		strcat(r, t);
	}

	va_end(ap);

	return r;
}

void seekFile() {
	int fd = open("E:/c.log", O_RDONLY, 0);
	int pos = lseek(fd, 10, 0);
	printf("pos:%d \n", pos);
	char data[10];
	read(fd, data, 10);
	printf("data:%s \n", data);
}

void sigHand(int sig) {
	printf("process %d\n", sig);
}

void handlerSignal() {
	printf("aaaaaaa\n");
	signal(SIGABRT, sigHand);
	printf("send %d\n", raise(SIGABRT));
	printf("end\n");
}

void getClock() {
	int i = 0;
	while (i++ < 100000000) {

	}
	printf("used:%d\n", clock());

	printf("now:%d\n", time(NULL));
}

char *say(char *words) {
	printf("invoke say function.\n");
	char *s = calloc(50, sizeof(char));
	strcat(s, "saying");
	strcat(s, words);
	printf("%s\n", s);
	return s;
}

char *say1(char *r, char *ws) {
	printf("%s\n", r);
	strcat(r, ws);
	printf("%s\n", r);
	return r;
}

void test() {
	int a;
	scanf("a=%d", &a);
	printf("%d", ++a);
}

void testMysql() {
	MYSQL mysql, *sock;   //声明MySQL的句柄
	const char * host = "127.0.0.1";  //因为是作为本机测试，所以填写的是本地IP
	const char * user = "root";       //这里改为你的用户名，即连接MySQL的用户名
	const char * passwd = ""; //这里改为你的用户密码
	const char * db = "test";      //这里改为你要连接的数据库的名字
	unsigned int port = 3306;           //这是MySQL的服务器的端口，如果你没有修改过的话就是3306。
	const char * unix_socket = NULL; //unix_socket这是unix下的，我在Windows下，所以就把它设置为NULL
	unsigned long client_flag = 0;      //这个参数一般为0

	const char * i_query = "select * from user"; //查询语句

	MYSQL_RES * result;                          //保存结果集的 www.2cto.com
	MYSQL_ROW row;                               //代表的是结果集中的一行

	mysql_init(&mysql);                          //连接之前必须使用这个函数来初始化
	if ((sock = mysql_real_connect(&mysql, host, user, passwd, db, port,
			unix_socket, client_flag)) == NULL) //连接MySQL
	{
		printf("连接失败，原因是: \n");
		fprintf(stderr, " %s\n", mysql_error(&mysql));
		exit(1);
	} else {
		fprintf(stderr, "连接MySQL成功！！\n");
	}

	if (mysql_query(&mysql, i_query) != 0)       //如果连接成功，则开始查询
			{
		fprintf(stderr, "查询失败！\n");
		exit(1);
	} else {
		if ((result = mysql_store_result(&mysql)) == NULL) //保存查询的结果
		{
			fprintf(stderr, "保存结果集失败！\n");
			exit(1);
		} else {
			while ((row = mysql_fetch_row(result)) != NULL) //读取结果集中的数据，返回的是下一行。因为保存结果集时，当前的游标在第一行【之前】
			{
				printf("name is %s\t", row[0]);               //打印当前行的第一列的数据
				printf("age is %s\t\n", row[1]);              //打印当前行的第二列的数据
			}
		}

	}
	mysql_free_result(result);                                //释放结果集
	mysql_close(sock);                                        //关闭连接
	system("pause");
	exit(EXIT_SUCCESS);
}

int compar (const void *a ,const void *b)
{
	int *aa=(int * ) a,*bb = (int * )b;
	if( * aa >* bb)return 1;
	if( * aa == * bb) return 0;
	if( * aa < *bb) return -1;
}
//快速排序
void testQsort(){
	int base[3]={1,3,2} ;
	int i;
	qsort(base,3,sizeof(int),compar);
	for(i=0;i<3;i++)
		printf("%d  ",base[i]);
	printf("\n");
}

//字符串搜索
int strcompar (const void *a,const void *b)
{
	return (strcmp((char *) a, (char *) b));
}
void testStrFind()
{
	char data[50][10]={"Linux","freebsd","solzris","sunos","windows"};
	char key[80],*base,*offset;
	int i, nmemb=50,size=10;
	for(i=1;i<5;i++)
	{
		fgets(key,sizeof(key),stdin);
		key[strlen(key)-1]='\0';
		base = data[0];
		offset = (char *)lfind(key,base,&nmemb,size,compar);
		if(offset ==NULL)
		{
			printf("%s not found!\n",key);
			offset=(char *) lsearch(key,base,&nmemb,size,compar);
			printf("Add %s to data array\n",offset);
		}
		else
		{
			printf("found : %s \n",offset);
		}
	}
}

//读文件到块
struct test                     	/*定义结构体*/
{
	char name[20];
	int pay;
}s[3];
#define set_s(x,y,z) {strcpy(s[x].name,y);s[x].pay=z;}   /*自定义宏，用于赋值*/
void testFwrite(){
	FILE * fp;                   	/*定义文件变量指针*/
	set_s(0,"张三",12345);
	set_s(1,"lisi",200);
	set_s(2,"wangwu",50000);
	fp=fopen("D:/b.txt","a+");	/*打开(创建)文件*/
	fwrite(s,sizeof(struct test),3,fp);/*调用fwite函数把块信息写入文件*/
	fclose(fp);
}
void testFread(){
	FILE * fp;              		/*定义文件变量指针*/
	int i;
	fp = fopen("D:/b.txt", "r");	/*打开文件*/
	fread(s,sizeof(struct test),3,fp);/*调用fread函数从文件读取块信息*/
	fclose(fp);                  			  /*关闭文件流*/
	for(i=0;i<3;i++)
		printf("帐号[%d]:%-20s余额[%d]:%d\n",i,s[i].name,i,s[i].pay);
}

//读取dir目录
void testOpenDir(){
	DIR * dir;
	struct dirent * ptr;
	int i;
	dir=opendir("D:/");
	while((ptr = readdir(dir))!=NULL)
	{
		printf("目录: %s\n",ptr->d_name);
	}
	closedir(dir);
}

void testFork(){
	pid_t pid;
	long c,i,j;
	for(i=0;i<5;i++){
//		pid = fork();	//windows没有fork()函数
		printf("main process pid:%d \n",pid);
	}
	for(j=0;j<3;j++){
		printf("pid:%d,c:%d \n",pid,c);
	}

}


