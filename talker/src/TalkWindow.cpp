/*
 * TalkWindow.cpp
 *
 *  Created on: 2014年12月9日
 *      Author: zjd
 */

#include "head/TalkWindow.h"
#include "email/head/EmailManage.h"
#include "email/head/Util.h"

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
#include <unistd.h>

using namespace std;
using namespace ns_email;

namespace ns_email {

TalkWindow::TalkWindow() {
	// TODO Auto-generated constructor stub

}

TalkWindow::~TalkWindow() {
	// TODO Auto-generated destructor stub
}

void TalkWindow::start(){
	cout<<"please input your name:\n"<<endl;
	scanf("%s",myName);
	cout<<"please input your friend's name:\n"<<endl;
	scanf("%s",friendName);
//	cout<<myName<<"====="<<friendName<<endl;
	startTalk();
}

void TalkWindow::startTalk(){
	Util util;
	EmailManage senderManage(QQ,"465824789",util.decodeBase64("empkOabcdefg"));
	EmailManage receiveManage(E126,"jindongzhao",util.decodeBase64("empkOabcdefg"));

	while(true){
		//发送消息
		char* myWords = new char[100];
		cout<<"please input your words:\n"<<endl;
		scanf("%s",myWords);
		senderManage.send("jindongzhao@126.com",util.stringCat("direct to:",friendName),
					util.stringCat(util.stringCat(myName, " saying:::"),myWords));

		//接收消息
		while(true){
//			cout<<"请输入回车，接收消息"<<endl;
//			char* a = new char[2];
//			scanf("%s",a);

			EmailContent* content = receiveManage.receive();
//			cout<<"消息内容："<<content->subject<<endl;
			if(strcasecmp(content->subject,util.stringCat("direct to:",myName)) == 0){	//发给自己的消息，显示
				cout<<content->content<<endl;
				break;
			}
			sleep(10);
		}
	}
}
} /* namespace ns_email */
