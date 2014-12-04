//============================================================================
// Name        : talker.cpp
// Author      : zjd
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sys/socket.h>
#include <iostream>

#include "head/Talker.h"
#include "email/head/Util.h"
#include "email/head/EmailManage.h"

using namespace std;
using namespace ns_email;

int main(){

		EmailManage manage(QQ,"465824789","***");	//邮箱用户名、密码
		manage.send("jindongzhao@126.com","ttttttttttttttttttttttt");

//	Util util;
//	cout<<util.stringCat("abc","def")<<std::endl;

	return 0;
}

int main1() {
	Talker talker;
	//const char *host = "smtp.126.com";
	const char *host = "smtp.qq.com";
	int port = 25; //smtp协议专用端口
	char wkstr[100] = "hello,how are you?zzzzzzzzzz"; //邮件内容
	if (talker.connectServer(host, port) == false) {
		return 1;
	}
	talker.receiveMsg();
	std::cout << "Client : connected! \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	/*EHLO指令是必须首先发的，相当于和服务器说hello*/
	//talker.sendMsg("EHLO jindongzhao@126.com\r\n"); //邮箱用户名
	talker.sendMsg("EHLO 465824789@qq.com\r\n"); //邮箱用户名
	talker.receiveMsg();
	std::cout << "Client : send helo \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	/*发送 auth login 指令，告诉服务器要登录邮箱*/
	talker.sendMsg("auth login\r\n");
	talker.receiveMsg();
	std::cout << "Client : send auth login \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	/*告诉服务器要登录后，接着就是把用户名发过去了.
	 不过这个用户名是经过了base64编码的，smtp也支持
	 明文传送，至于具体有什么区别上网上找资料看看就知道了*/
	talker.sendMsg("NDY1ODI0Nzg5QHFxLmNvbQ=="); //经过base64编码后的邮箱用户名
	talker.sendMsg("\r\n");
	talker.receiveMsg();
	std::cout << "Client : send name \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	/*用户名发过去后接着就是用户密码了，当然也是经过base64编码后的*/
	talker.sendMsg("empkODYxMDAx");
	talker.sendMsg("\r\n");
	talker.receiveMsg();
	std::cout << "Client : send password \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	/*发送 mail from 指令，相当于填写发件人*/
	talker.sendMsg("mail from <");
	//talker.sendMsg("jindongzhao@126.com");
	talker.sendMsg("465824789@qq.com");
	talker.sendMsg(">");
	talker.sendMsg("\r\n");
	talker.receiveMsg();
	std::cout << "Client: send mail from \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	/*发送 rcpt to 指令，就是填写收件人了 */
	talker.sendMsg("rcpt to <");
	talker.sendMsg("jindongzhao@126.com");
	talker.sendMsg(">");
	talker.sendMsg("\r\n");
	talker.receiveMsg();
	std::cout << "Client : send rcpt to \nServer" << talker.getReceiveBuf()
			<< std::endl;

	/*发送data,标志着后面开始发送邮件的主题部分*/
	talker.sendMsg("data\r\n");
	talker.receiveMsg();
	std::cout << "Client : send data \nServer :" << talker.getReceiveBuf()
			<< std::endl;
	/*发送邮件主体部分，先是邮件主题（subject）,后面是邮件内容。
	 下面就是发送主体的格式*/
	talker.sendMsg("subject:");
	talker.sendMsg("test mail\r\n");
	talker.sendMsg("\r\n\r\n");
	talker.sendMsg("hello,howare you.\r\n");
	talker.sendMsg(".\r\n");
	talker.receiveMsg();
	std::cout << "Client : send content \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	talker.sendMsg("quit\r\n");
	talker.receiveMsg();
	std::cout << "Client : send quit \nServer :" << talker.getReceiveBuf()
			<< std::endl;

	return 0;
}
