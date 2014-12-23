/*
 * Sender.h
 *
 *  Created on: 2014年12月22日
 *      Author: zjd
 */

#ifndef INTERFACE_SENDER_H_
#define INTERFACE_SENDER_H_

#include "../bo/User.h"
#include "../bo/Message.h"

namespace ns_talker {

class Sender {
public:
	Sender();
	virtual ~Sender();

	virtual void init(User& me,User& other) = 0;
	virtual void send(Message& msg) = 0;
};

} /* namespace ns_talker */

#endif /* INTERFACE_SENDER_H_ */
