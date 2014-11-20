/*4-13.c程序：文件的定位*/  
#include<stdio.h>

int main()
{
	FILE *stream;
	long offset;
	fpos_t pos;
	stream=fopen("/etc/passwd","r");
	fseek(stream,10,SEEK_SET);
	printf("文件流的偏移量：%d\n",ftell(stream));
	fseek(stream,0,SEEK_END);
	printf("文件流的偏移量：%d\n",ftell(stream));
	rewind(stream);
	printf("文件流的偏移量：%d\n",ftell(stream));
	fclose(stream);
	return 0;
}
