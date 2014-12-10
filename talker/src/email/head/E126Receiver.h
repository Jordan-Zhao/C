/*
 * QqReceiver.h
 *
 *  Created on: 2014年12月5日
 *      Author: zjd
 */

#ifndef EMAIL_QQRECEIVER_H_
#define EMAIL_QQRECEIVER_H_

#define BUF_SIZE 1024*30

#include "Util.h"
#include "EmailReceiver.h"

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>

struct hostent;
struct sockaddr_in;
namespace ns_email {
class Util;
} /* namespace ns_email */

namespace ns_email {

class E126Receiver : public  EmailReceiver{
public:
	E126Receiver(char* username,char* pwd);
	virtual ~E126Receiver();

	EmailContent* receiveMsg();

private:
	Util* util;
	char *host = "126.com";
	int port = 110; //smtp协议专用端口
	char* userAddr;
	char* username;
	char* pwd;
	int sock;
	char receiveBuf[BUF_SIZE];//接收登录信息从Server传回来的数据
	struct sockaddr_in server;
	struct hostent *hp;//通过地址获取完整的服务器地址

	int emailCount = 0;

	void initSocket();
	void connectServer();
	void login(char* username, char* pwd);
	void deleteEmail(int num);
	void loginOut();
	void sendSocketMsg(int sock, char* msg);
	int receiveSocketMsg(int sock, char* buf);

	EmailContent* getEmailContent(int idx);

};

} /* namespace ns_email */

#endif /* EMAIL_QQRECEIVER_H_ */
