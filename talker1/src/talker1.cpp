//============================================================================
// Name        : talker1.cpp
// Author      : zjd
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include "bo/Message.h"
#include "bo/User.h"
#include "interface/Sender.h"
#include "comps/email/QqSender.h"
#include "interface/Receiver.h"
#include "comps/email/E126Receiver.h"

using namespace std;
using namespace ns_talker;

int main() {
	User me;
	me.setId("Jack");
	User other;
	other.setId("Marry");
	Message msg;
	msg.setContent("wwwwwwww");

	Sender* sender = new QqSender();
	sender->init(me,other);
	for(int i=0;i<1;i++){
		sender->send(msg);
	}

	sleep(10);

	Receiver* receiver = new E126Receiver();
	receiver->init(other);
	Message m = receiver->receive();

//	cout<<"++++++++++++++\n"<<m.getContent()<<endl;

//	cout<<Util::Base64Encode(string("465824789@qq.com\r\n"))<<endl;

	return 0;
}
