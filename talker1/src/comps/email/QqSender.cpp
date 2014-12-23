/*
 * QqSender.cpp
 *
 *  Created on: 2014年12月23日
 *      Author: zjd
 */

#include "QqSender.h"
#include "../../common/CommonHeader.h"
#include "../../interface/Sender.h"
#include "../../bo/User.h"
#include "../../bo/Message.h"

using namespace std;

namespace ns_talker {

QqSender::QqSender() {
}

QqSender::~QqSender() {
	delete me;
	delete other;
}

void QqSender::init(User& me, User& other) {
	this->me = &me;
	this->other = &other;
}
void QqSender::send(Message& msg) {
	char receiveBuf[BUFSIZ];

	//初始化socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		throw std::runtime_error("qq sender 初始化socket异常 \n");
	}

	//连接服务端
	struct sockaddr_in server;
	struct hostent* hp;
	server.sin_family = AF_INET;
	hp = gethostbyname("smtp.qq.com");
	if (hp == (struct hostent *) 0) {
		std::cerr << "qq sender 服务器地址获取失败！" << std::endl;
	}
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(25);
	if (connect(sock, (sockaddr *) &server, sizeof server) == -1) {
		std::cerr << "qq sender 连接服务器失败！" << std::endl;
	}
	Util::receiveSocketMsg(sock,receiveBuf);
	std::cout << "qq sender 连接服务器成功。服务器返回：" << receiveBuf << std::endl;
//	free(&server);
//	delete hp;

	//登录
	/*EHLO指令是必须首先发的，相当于和服务器说hello*/
	Util::sendSocketMessage(sock,string("EHLO 465824789@qq.com"));
	Util::sendSocketMessage(sock,string("\r\n"));
	Util::receiveSocketMsg(sock,receiveBuf);
	std::cout << "qq sender 发送hello信息。服务器返回 :" << receiveBuf << std::endl;

	/*发送 auth login 指令，告诉服务器要登录邮箱*/
	Util::sendSocketMessage(sock, string("auth login\r\n"));
	Util::receiveSocketMsg(sock, receiveBuf);
	std::cout << "qq sender 发送登陆指令。服务器返回 :" << receiveBuf << std::endl;

	/*这个用户名是经过了base64编码的，smtp也支持明文传送*/
	Util::sendSocketMessage(sock, Util::Base64Encode(string("465824789@qq.com")));
	Util::sendSocketMessage(sock, string("\r\n"));
	Util::receiveSocketMsg(sock, receiveBuf);
	std::cout << "qq sender发送登录用户名。服务器返回 :" << receiveBuf << std::endl;

	/*用户名发过去后接着就是用户密码了，当然也是经过base64编码后的*/
	Util::sendSocketMessage(sock, Util::Base64Encode(string("zjd861001")));
	Util::sendSocketMessage(sock, string("\r\n"));
	Util::receiveSocketMsg(sock, receiveBuf);
	std::cout << "qq sender发送登录密码。服务器返回 :" << receiveBuf<< std::endl;

	/*发送 mail from 指令，相当于填写发件人*/
	Util::sendSocketMessage(sock, string("mail from <465824789@qq.com>\r\n"));
	Util::receiveSocketMsg(sock, receiveBuf);
	std::cout << "qq sender发送 发件人 信息。服务器返回 :" << receiveBuf << std::endl;

	/*发送 rcpt to 指令，就是填写收件人了 */
	Util::sendSocketMessage(sock, string("rcpt to <jindongzhao@126.com>\r\n"));
	Util::receiveSocketMsg(sock, receiveBuf);
	std::cout << "qq sender 发送 收件人 信息。服务器返回：" << receiveBuf << std::endl;

	/*发送data,标志着后面开始发送邮件的主题部分*/
	Util::sendSocketMessage(sock, string("data\r\n"));
	Util::receiveSocketMsg(sock, receiveBuf);
	 std::cout << "qq sender 发送data命令，准备发送邮件主体。服务器返回:" << receiveBuf << std::endl;

	/*发送邮件主体部分，先是邮件主题（subject）,后面是邮件内容。*/
	Util::sendSocketMessage(sock, string( "subject:"));
	Util::sendSocketMessage(sock, "^^^^^^^^^^"+me->getId()+"&&&&&&&&&&"+other->getId()+"##########");
	Util::sendSocketMessage(sock, string( "\r\n\r\n"));	//必须，否则内容为空
	Util::sendSocketMessage(sock, ">>>>>>>>>>"+msg.getContent()+"<<<<<<<<<<");
	Util::sendSocketMessage(sock, string("\r\n.\r\n"));		//必须是这种格式，否则无法收到邮件
	Util::receiveSocketMsg(sock, receiveBuf);
	std::cout << "qq sender 发送邮件主体。服务器返回:" << receiveBuf << std::endl;

	//退出
	Util::sendSocketMessage(sock, string("quit\r\n"));
	Util::receiveSocketMsg(sock, receiveBuf);
	std::cout << "qq sender 退出邮件回话。服务器返回 :" << receiveBuf << std::endl;
}
} /* namespace ns_talker */
