/*
 * E126Receiver.cpp
 *
 *  Created on: 2014年12月5日
 *      Author: zjd
 */

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdexcept>
#include <stdlib.h>
#include <sstream>
#include "head/E126Receiver.h"

using namespace std;
namespace ns_email {

E126Receiver::E126Receiver(char* username,char* pwd) {
	this->username = username;
	this->pwd = pwd;
}

E126Receiver::~E126Receiver() {
	delete util;
}

EmailContent* E126Receiver::receiveMsg(){
	initSocket();
	connectServer();
	login(username,pwd);

	//获取stat
//	sendSocketMsg(sock,"stat \r\n");
//	receiveSocketMsg(sock,receiveBuf);
//	strlen(receiveBuf);
//	sizeof(receiveBuf);
//	util->stringCat(receiveBuf," ");
//	cout << receiveBuf << std::endl;

	//获取最后一封邮件内容
	EmailContent* content = getEmailContent(emailCount);

	deleteEmail(emailCount);

	//退出stocket
	loginOut();

	return content;
}

void E126Receiver::initSocket(){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		throw std::runtime_error("socket init error\n");
	}
}
void E126Receiver::connectServer(){
	server.sin_family = AF_INET;
	hp = gethostbyname(util->stringCat("pop.", host));
	if (hp == (struct hostent *) 0) {
		std::cerr << "服务器地址获取失败！" << std::endl;
	}
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(port);
	if (connect(sock, (sockaddr *) &server, sizeof server) == -1) {
		std::cerr << "连接服务器失败！" << std::endl;
	}
	receiveSocketMsg(sock, receiveBuf);
//	std::cout << "Client : connected! \nServer :" << receiveBuf << std::endl;
}

void E126Receiver::login(char* username, char* pwd){
	userAddr = util->stringCat(username, util->stringCat("@", host));

	//发送用户名
    sendSocketMsg(sock,util->stringCat(util->stringCat("user ",userAddr)," \r\n"));//邮箱地址
	receiveSocketMsg(sock,receiveBuf);
//	std::cout << "Client : send user \nServer:" <<receiveBuf << std::endl;

	//发送密码
	sendSocketMsg(sock,"pass zjd861001\r\n");//邮箱地址
	receiveSocketMsg(sock,receiveBuf);
//	std::cout << "Client : send pass \nServer:" <<receiveBuf << std::endl;

	//获取邮件总数
	emailCount = util->str2num(util->strSub(receiveBuf,"OK "," message"));

}

void E126Receiver::deleteEmail(int num){
	sendSocketMsg(sock,util->stringCat(util->stringCat("dele  ",util->num2str(num)),"\r\n"));
	receiveSocketMsg(sock,receiveBuf);
}

void E126Receiver::loginOut(){
		sendSocketMsg(sock,"quit  \r\n");
		receiveSocketMsg(sock,receiveBuf);
//		std::cout << "receiver socket quit.  \nServer:" <<receiveBuf << std::endl;
}

void E126Receiver::sendSocketMsg(int sock, char* msg){
	send(sock, msg, strlen(msg), 0);
}

int E126Receiver::receiveSocketMsg(int sock, char* buf){
	memset(buf, 0, BUF_SIZE);
	return recv(sock, buf, BUF_SIZE, 0);
}

EmailContent*  E126Receiver::getEmailContent(int idx){
	//TODO:为什么需要先按以下方式把receiveBuf输出到一个流里，才能再接收新的数据？
	stringstream ss;
	ss<<"cccc"<<receiveBuf<<std::endl;
	ss.clear();

	EmailContent* ec = (EmailContent*)malloc(sizeof(EmailContent));

//	char* receiveBuf1 = (char*)malloc(BUF_SIZE);
	sendSocketMsg(sock,util->stringCat(util->stringCat("RETR  ",util->num2str(idx)),"\r\n"));
	receiveSocketMsg(sock,receiveBuf);
	strlen(receiveBuf);
//	std::cout << "Client : 获取最后信件内容  \nServer:" <<receiveBuf << std::endl;

	char* s1 = util->trim(util->strSub(receiveBuf,"Sender: ","\n"));
	std::string s2 = s1;
	int a = -1;
	if((a = s2.find_first_of("\r")) > -1){
		ec->from = new char[s2.length()];
	    strcpy(ec->from,s2.substr(0,a).data());
	}else{
		ec->from = s1;
	}
	ec->subject = util->trim(util->strSub(receiveBuf,"subject:","\n"));
	char* s = strstr(util->strSub(receiveBuf,"From: ","\n."),"\n");
	ec->content =util->trim(s);
//	ec->content =s;

//	delete rs;
	return ec;
}

} /* namespace ns_email */
