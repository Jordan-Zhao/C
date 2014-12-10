/*
 * EmailSender.h
 *
 *  Created on: 2014年12月3日
 *      Author: zjd
 */

#ifndef EMAIL_EMAILSENDER_H_
#define EMAIL_EMAILSENDER_H_

namespace ns_email {

class EmailSender {
public:
	EmailSender();
	virtual ~EmailSender();

	virtual void sendMsg(char* toAddr,char* subject, char* content) = 0;
};

} /* namespace ns_email */

#endif /* EMAIL_EMAILSENDER_H_ */
