/*
 * Talker.h
 *
 *  Created on: 2014年12月3日
 *      Author: zjd
 */

#ifndef TALKER_H_
#define TALKER_H_

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <netinet/in.h>

class Talker {
public:
	Talker();
	virtual ~Talker();

	bool connectServer(const char *host_id, const int &port);
	void sendMsg(const char *s);
	int receiveMsg();
	const char * getReceiveBuf();
private:
	char receiveBuf[BUFSIZ];
	int sock;
	int num;
	struct sockaddr_in server;
	struct hostent *hp;
};

#endif /* TALKER_H_ */
