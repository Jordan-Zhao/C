/*
 * Message.cpp
 *
 *  Created on: 2014年12月22日
 *      Author: zjd
 */
#include "../common/CommonHeader.h"
#include "Message.h"

using namespace std;

namespace ns_talker {

Message::Message() { }

Message::~Message() {
//	delete content.data();
//	delete fromUser;
//	delete toUser;
}

string Message::getContent(){
	return content;
}

void Message::setContent(string ctn){
	content = ctn;
}

string Message::getFromUserId(){
	return fromUserId;
}

void Message::setFromUserId(string userId){
	fromUserId = userId;
}

string Message::getToUserId(){
	return toUserId;
}

void Message::setToUserId(string userId){
	toUserId = userId;
}

} /* namespace ns_talker */
