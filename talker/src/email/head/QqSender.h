/*
 * QqSender.h
 *
 *  Created on: 2014年12月4日
 *      Author: zjd
 */

#ifndef EMAIL_QQSENDER_H_
#define EMAIL_QQSENDER_H_

#include "Util.h"
#include "EmailSender.h"

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>

namespace ns_email {

class QqSender : public EmailSender {
public:
	QqSender(char* username, char* pwd);
	~QqSender();

	void sendMsg(char* toAddr,char* subject, char* content);

private:
	Util* util;
	char *host = "qq.com";
	int port = 25; //smtp协议专用端口

	char* username;
	char* pwd;
	char* fromAddr;
	int sock;
	char receiveBuf[BUFSIZ];
	int num;
	struct sockaddr_in server;
	struct hostent *hp;

	void initSocket();
	void connectServer();
	void login(char* username, char* pwd);
	void loginOut();
	void sendSocketMsg(int sock, char* msg);
	int receiveSocketMsg(int sock, char* buf);

};

} /* namespace ns_email */

#endif /* EMAIL_QQSENDER_H_ */
