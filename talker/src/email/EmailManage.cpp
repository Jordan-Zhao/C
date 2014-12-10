/*
 * EmailManage.cpp
 *
 *  Created on: 2014年12月3日
 *      Author: zjd
 */

#include "head/EmailManage.h"

#include "head/E126Receiver.h"
#include "head/QqSender.h"

namespace ns_email {

EmailManage::EmailManage() {

}

EmailManage::EmailManage(EmailType t, char* username, char* pwd) {
	if (t == QQ) {
		sender = new QqSender(username, pwd);
	}else if (t == E126) {
		receiver = new E126Receiver(username,pwd);
	}
}

EmailManage::~EmailManage() {
	delete sender;
}

void EmailManage::send(char* toAddr,char* subject, char* msg) {
	cout << "发送消息："<<msg<<endl;
	sender->sendMsg(toAddr,subject, msg);
}

EmailContent* EmailManage::receive(){
	cout << "接收消息."<<endl;
	return receiver->receiveMsg();
}

} /* namespace ns_email */
