/*
 * QqSender.cpp
 *
 *  Created on: 2014年12月4日
 *      Author: zjd
 */

#include "head/QqSender.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdexcept>

using namespace std;

namespace ns_email {

void QqSender::initSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		throw std::runtime_error("socketinit error\n");
	}
}
void QqSender::connectServer() {
	server.sin_family = AF_INET;
	hp = gethostbyname(util->stringCat("smtp.", host));
	if (hp == (struct hostent *) 0) {
		std::cerr << "服务器地址获取失败！" << std::endl;
	}
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(port);
	if (connect(sock, (sockaddr *) &server, sizeof server) == -1) {
		std::cerr << "连接服务器失败！" << std::endl;
	}
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : connected! \nServer :" << receiveBuf << std::endl;
}

void QqSender::login(char* username, char* pwd) {
	fromAddr = util->stringCat(username, util->stringCat("@", host));
	/*EHLO指令是必须首先发的，相当于和服务器说hello*/
	sendSocketMsg(sock,util->stringCat("EHLO ",fromAddr));	//邮箱用户名
	sendSocketMsg(sock, "\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send helo \nServer :" << receiveBuf
			<< std::endl;

	/*发送 auth login 指令，告诉服务器要登录邮箱*/
	sendSocketMsg(sock, "auth login\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send auth login \nServer :" << receiveBuf
			<< std::endl;

	/*告诉服务器要登录后，接着就是把用户名发过去了.
	 不过这个用户名是经过了base64编码的，smtp也支持
	 明文传送，至于具体有什么区别上网上找资料看看就知道了*/
	sendSocketMsg(sock, util->encodeBase64(fromAddr)); //经过base64编码后的邮箱用户名
	sendSocketMsg(sock, "\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send name \nServer :" << receiveBuf
			<< std::endl;

	/*用户名发过去后接着就是用户密码了，当然也是经过base64编码后的*/
	sendSocketMsg(sock, util->encodeBase64(pwd));
	sendSocketMsg(sock, "\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send password \nServer :" << receiveBuf<< std::endl;
}

void QqSender::loginOut() {
	sendSocketMsg(sock, "quit\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send quit \nServer :" << receiveBuf
			<< std::endl;
}

void QqSender::sendSocketMsg(int sock, char* msg) {
	send(sock, msg, strlen(msg), 0);
}

int QqSender::receiveSocketMsg(int sock, char* buf) {
	memset(buf, 0, BUFSIZ);
	return recv(sock, buf, BUFSIZ, 0);
}

QqSender::QqSender(char* username, char* pwd) {
	initSocket();
	connectServer();
	login(username, pwd);
}
QqSender::~QqSender() {
	loginOut();
	delete util;
}

void QqSender::sendMsg(char* toAddr, char* content) {
	/*发送 mail from 指令，相当于填写发件人*/
	sendSocketMsg(sock, "mail from <");
	sendSocketMsg(sock, fromAddr);
	sendSocketMsg(sock, ">");
	sendSocketMsg(sock, "\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client: send mail from \nServer :" << receiveBuf
			<< std::endl;

	/*发送 rcpt to 指令，就是填写收件人了 */
	sendSocketMsg(sock, "rcpt to <");
	sendSocketMsg(sock, toAddr);
	sendSocketMsg(sock, ">");
	sendSocketMsg(sock, "\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send rcpt to \nServer" << receiveBuf
			<< std::endl;

	/*发送data,标志着后面开始发送邮件的主题部分*/
	sendSocketMsg(sock, "data\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send data \nServer :" << receiveBuf
			<< std::endl;
	/*发送邮件主体部分，先是邮件主题（subject）,后面是邮件内容。
	 下面就是发送主体的格式*/
	sendSocketMsg(sock, "subject:");
	sendSocketMsg(sock, "test mail from c++ client\r\n");
	sendSocketMsg(sock, "\r\n\r\n");
	sendSocketMsg(sock, util->stringCat(content,"\r\n"));
	sendSocketMsg(sock, ".\r\n");
	receiveSocketMsg(sock, receiveBuf);
	std::cout << "Client : send content \nServer :" << receiveBuf
			<< std::endl;
}

} /* namespace ns_email */
