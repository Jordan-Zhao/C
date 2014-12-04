/*
 * EmailManage.h
 *
 *  Created on: 2014年12月3日
 *      Author: zjd
 */

#ifndef EMAIL_EMAILMANAGE_H_
#define EMAIL_EMAILMANAGE_H_

#include "EmailSender.h"

namespace ns_email {

/**
 * 邮箱类型
 */
enum EmailType {
	QQ = 1, E163 = 2
};

class EmailManage {
private:
	EmailSender* sender;
public:
	EmailManage();
	EmailManage(EmailType t, char* username, char* pwd);
	virtual ~EmailManage();

	void send(char* toAddr, char* msg);
};

} /* namespace ns_email */

#endif /* EMAIL_EMAILMANAGE_H_ */
