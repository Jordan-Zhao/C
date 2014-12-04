/*
 * EmailManage.cpp
 *
 *  Created on: 2014年12月3日
 *      Author: zjd
 */

#include "head/EmailManage.h"

#include "head/QqSender.h"

namespace ns_email {

EmailManage::EmailManage() {

}

EmailManage::EmailManage(EmailType t, char* username, char* pwd) {
	if (t == QQ) {
		sender = new QqSender(username, pwd);
	}
}

EmailManage::~EmailManage() {
	delete sender;
}

void EmailManage::send(char* toAddr, char* msg) {
	sender->sendMsg(toAddr, msg);
}

} /* namespace ns_email */
