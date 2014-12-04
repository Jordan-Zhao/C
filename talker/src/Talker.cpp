/*
 * Talker.cpp
 *
 *  Created on: 2014年12月3日
 *      Author: zjd
 */

#include "head/Talker.h"

#include  <sys/socket.h>
#include <stdexcept>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

Talker::Talker() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		throw std::runtime_error("socketinit error\n");
	}

}

Talker::~Talker() {
	close(sock);
}

bool Talker::connectServer(const char *host, const int &port) {
	server.sin_family = AF_INET;
	hp = gethostbyname(host);
	if (hp == (struct hostent *) 0) {
		std::cerr << "服务器地址获取失败！" << std::endl;
		return false;
	}
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(port);
	if (connect(sock, (sockaddr *) &server, sizeof server) == -1) {
		std::cerr << "连接服务器失败！" << std::endl;
		return false;
	} else
		return true;
}

void Talker::sendMsg(const char *s) {
	send(sock, s, strlen(s), 0);
}
int Talker::receiveMsg() {
	memset(receiveBuf, 0, BUFSIZ);
	return recv(sock, receiveBuf, BUFSIZ, 0);
}
const char * Talker::getReceiveBuf() {
	return receiveBuf;
}

