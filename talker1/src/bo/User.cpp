/*
 * User.cpp
 *
 *  Created on: 2014年12月22日
 *      Author: zjd
 */

#include "../common/CommonHeader.h"

#include "User.h"

namespace ns_talker {

User::User() { }

User::~User() {
//	cout<<"xigou user"<<endl;
}

string User::getId(){
	return id;
}
void User::setId(string id){
	this->id = id;
}
} /* namespace ns_talker */
