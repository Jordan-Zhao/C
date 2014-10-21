#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>

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

int scanftest(){
	int y,m;
	char d[2];
	int n = scanf("%d-%d-%s",&y,&m,d);
	printf("%d result: %d/%d/%s \n",n,y,m,d);
	return n;
}

void filetest1(){
	char a = getc(stdin);
	putc(a,stderr);
}

void log1(char *msg){
	FILE *f=fopen("E:/c.log","a");
	while(*msg != '\0'){
		putc(*msg++,f);
	}
	putc('\n',f);
	fclose(f);
}

void systemtest(){
	system("date");
}

void outFileContent(){
	int fd = open("E:/c.log",O_RDONLY,0);
	char content[100];
	int r= read(fd,content,100);
	printf("%s \t %d \n",content,sizeof(content));
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

void seekFile(){
	int fd = open("E:/c.log",O_RDONLY,0);
	int pos = lseek(fd,10,0);
	printf("pos:%d \n",pos);
	char data[10];
	read(fd,data,10);
	printf("data:%s \n",data);
}

void sigHand(int sig){
	printf("process %d\n",sig);
}

void handlerSignal(){
	printf("aaaaaaa\n");
	signal(SIGABRT,sigHand);
	printf("send %d\n",raise(SIGABRT));
	printf("end\n");
}

void getClock(){
	int i=0;
	while(i++<100000000){

	}
	printf("used:%d\n",clock());

	printf("now:%d\n",time(NULL));
}

