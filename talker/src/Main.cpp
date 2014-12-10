//============================================================================
// Name        : talker.cpp
// Author      : zjd
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdexcept>s

#include "email/head/Util.h"
#include "email/head/EmailManage.h"
#include "head/TalkWindow.h"

using namespace std;
using namespace ns_email;

int main(){
	try{
		TalkWindow window;
		window.start();
	}catch (std::exception e) {
		cout<<e.what()<<endl;
	}

//		EmailManage qqManage(QQ,"465824789","zjd861001");	//邮箱用户名、密码
//		qqManage.send("jindongzhao@126.com","zhang san","hello worldccc");
//
//		EmailManage e126Manage(E126,"jindongzhao","zjd861001");	//邮箱用户名、密码
//		EmailContent* content = e126Manage.receive();
//		cout<<"from:"<<content->from<<std::endl;
//		cout<<"subject:"<<content->subject<<std::endl;
//		cout<<"content:"<<content->content<<std::endl;

//		Util util;
//		char* s ="zjd861001";
//		cout<<util.encodeBase64(s)<<endl;
//		std::cout << util.decodeBase64(util.encodeBase64(s))<< std::endl;

	return 0;
}

