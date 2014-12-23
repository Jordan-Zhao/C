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
}

string Message::getContent(){
	return content;
}

void Message::setContent(string ctn){
	content = ctn;
}

} /* namespace ns_talker */
