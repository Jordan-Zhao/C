/*1-4、c程序：把输入的字符串原样输出*/
#include <my.h>            			/*文件预处理，包含自定义的库文件"my.h"*/
int main()                      		/*C程序的主函数，开始入口*/
{
		char ch;
		while((ch=getchar())!=EOF)  	/*判断输入是否结束，终端下按回车结束输入*/
			putchar(ch);              	/*输出字符串*/
		return 1;
}
