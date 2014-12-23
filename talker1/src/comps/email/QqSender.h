/*
 * QqSender.h
 *
 *  Created on: 2014年12月23日
 *      Author: zjd
 */

#ifndef COMPS_EMAIL_QQSENDER_H_
#define COMPS_EMAIL_QQSENDER_H_

#include "../../common/CommonHeader.h"
#include "../../interface/Sender.h"
#include "../../bo/User.h"
#include "../../bo/Message.h"

using namespace std;

namespace ns_talker {

class QqSender : public Sender{
public:
	QqSender();
	virtual ~QqSender();

	void init(User& me,User& other) ;
	void send(Message& msg) ;

private:
	User* me;
	User* other;
};

} /* namespace ns_talker */

#endif /* COMPS_EMAIL_QQSENDER_H_ */
